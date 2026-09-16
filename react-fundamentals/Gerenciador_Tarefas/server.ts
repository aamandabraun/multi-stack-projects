import express from "express";
import Database from "better-sqlite3";

const app = express();
const PORT = Number(process.env.PORT) || 3000;

// Middleware para ler JSON
app.use(express.json());

const db = new Database("tarefas.db");

db.exec(` 
    CREATE TABLE IF NOT EXISTS tarefas (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        titulo TEXT NOT NULL,
        prioridade TEXT DEFAULT 'medium',
        status TEXT DEFAULT 'pending'
    );

    CREATE TABLE IF NOT EXISTS usuarios (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        senha TEXT NOT NULL,
        email TEXT NOT NULL
    );
`);

const usuariosExistentes = db.prepare("SELECT COUNT(*) AS count FROM usuarios").get() as any;
if (usuariosExistentes.count === 0) {

db.prepare( "INSERT INTO usuarios (senha, email) VALUES ('admin123', 'admin@exemplo.com')").run();
}

console.log("Banco de dados inicializado com sucesso!");

// ================================================
// TIPOS
// ================================================
interface Tarefa {
    id: number;
    titulo: string;
    prioridade: string;
    status: string;
}

// ================================================
// CONSTANTES (Allowlists)
// ================================================
const PRIORIDADES = ["low", "medium", "high"] as const;
const STATUS_VALIDOS = ["pending", "completed"] as const;

// ================================================
// HELPERS REUTILIZÁVEIS DE VALIDAÇÃO
// ================================================

// Type guard: garante que o título é uma string válida
// (mínimo de 3 caracteres úteis após o trim)
function tituloValido(valor: unknown): valor is string {
    return typeof valor === "string" && valor.trim().length >= 3;
}

// Allowlist com valor padrão seguro: se vier algo fora da lista,
// o cliente recebe um comportamento previsível em vez de um erro 500.
function normalizarPrioridade(valor: unknown): typeof PRIORIDADES[number] {
    return PRIORIDADES.includes(valor as typeof PRIORIDADES[number])
        ? (valor as typeof PRIORIDADES[number])
        : "medium";
}

function normalizarStatus(valor: unknown): typeof STATUS_VALIDOS[number] {
    return STATUS_VALIDOS.includes(valor as typeof STATUS_VALIDOS[number])
        ? (valor as typeof STATUS_VALIDOS[number])
        : "pending";
}

// Padroniza a conversão/validação de IDs vindos da URL (params),
// eliminando a duplicação de parseInt + isNaN em cada rota.
function parsearId(valor: string): number | null {
    const id = parseInt(valor, 10);
    return isNaN(id) ? null : id;
}

// ================================================
// PREPARED STATEMENTS SINGLETON (reuso nas rotas)
// ================================================
const stmtInserirTarefa = db.prepare(
    "INSERT INTO tarefas (titulo, status, prioridade) VALUES (?, 'pending', ?)"
);
const stmtBuscarPorId = db.prepare("SELECT * FROM tarefas WHERE id = ?");
const stmtDeletarTarefa = db.prepare("DELETE FROM tarefas WHERE id = ?");

// ================================================
// ROTAS DE LEITURA (GET)
// ================================================
app.get("/api/tasks", (req, res) => {
    const { search } = req.query;
    try {
    if (search) {
        // Prepared Statement: O '?' protege contra Injeção de SQL.
        const sql = "SELECT * FROM tarefas WHERE titulo LIKE ?";
        const tarefas = db.prepare(sql).all(`%${search}%`);
        res.json(tarefas);
    } else {
            const tarefas = db.prepare("SELECT * FROM tarefas").all();
            res.json(tarefas);
        }
    } catch (erro) {
        // Exibir o erro real ajuda a compreender a quebra de sintaxe gerada pelo ataque
        res.status(500).json({ error: erro instanceof Error ? erro.message : "Erro desconhecido" });
    }
});

// ================================================
// POST - Criação de tarefas
// ================================================
app.post("/api/tasks", (req, res) => {
    const { title, prioridade } = req.body;
    const prioridadeValida = normalizarPrioridade(prioridade);

    // Validação via helper (type guard)
    if (!tituloValido(title)) {
        return res.status(400).json({
            error: "O título da tarefa é obrigatório e deve conter pelo menos 3 caracteres válidos."
        });
    }

    try {
        const resultado = stmtInserirTarefa.run(title.trim(), prioridadeValida);
        const novaTarefa = stmtBuscarPorId.get(resultado.lastInsertRowid) as Tarefa;
        return res.status(201).json(novaTarefa);
    } catch {
        return res.status(500).json({ error: "Erro ao processar persistência" });
    }
});

// ================================================
// DELETE - Exclusão de tarefas
// ================================================
app.delete("/api/tasks/:id", (req, res) => {
    // Validação de ID padronizada (igual PUT/PATCH)
    const idParaDeletar = parsearId(req.params.id);
    if (idParaDeletar === null) {
        return res.status(400).json({ error: "ID inválido." });
    }

    try {
        const resultado = stmtDeletarTarefa.run(idParaDeletar);
        if (resultado.changes === 0) {
            return res.status(404).json({ error: "Tarefa não localizada para exclusão." });
        }
        res.json({ message: "Tarefa excluída do banco SQLite com sucesso!" });
    } catch {
        res.status(500).json({ error: "Erro interno ao processar a exclusão." });
    }
});

// ================================================
// PUT - Atualização completa
// ================================================
app.put("/api/tasks/:id", (req, res) => {
    const idParaAtualizar = parsearId(req.params.id);
    if (idParaAtualizar === null) {
        return res.status(400).json({ error: "ID inválido." });
    }

    const { title, prioridade, status } = req.body;

    // Validação via helpers
    if (!tituloValido(title)) {
        return res.status(400).json({
            error: "O título da tarefa é obrigatório e deve conter pelo menos 3 caracteres válidos."
        });
    }

    const prioridadeValida = normalizarPrioridade(prioridade);
    const statusValido = normalizarStatus(status);

    try {
        // Prepared statement inline (UPDATE completo não tem statement fixo no topo)
        const sql = "UPDATE tarefas SET titulo = ?, status = ?, prioridade = ? WHERE id = ?";
        const resultado = db.prepare(sql).run(title.trim(), statusValido, prioridadeValida, idParaAtualizar);

        if (resultado.changes === 0) {
            return res.status(404).json({ message: "Tarefa não encontrada para atualização!" });
        }

        const tarefaAtualizada = stmtBuscarPorId.get(idParaAtualizar) as Tarefa;
        return res.status(200).json(tarefaAtualizada);
    } catch {
        return res.status(500).json({ error: "Erro ao processar a atualização no banco de dados." });
    }
});

// ================================================
// PATCH - Atualização parcial (com transação)
// ================================================
app.patch("/api/tasks/:id", (req, res) => {
    const idParaAtualizar = parsearId(req.params.id);
    if (idParaAtualizar === null) {
        return res.status(400).json({ error: "ID inválido." });
    }

    if (!req.body || Object.keys(req.body).length === 0) {
        return res.status(400).json({ error: "Nenhum campo fornecido para atualização." });
    }

    const { title, prioridade, status } = req.body;

    try {
        const fluxoAtualizacao = db.transaction(() => {
            // Busca com statement singleton
            const tarefaExistente = stmtBuscarPorId.get(idParaAtualizar) as Tarefa | undefined;
            if (!tarefaExistente) return null;

            const camposParaAtualizar: string[] = [];
            const valoresParaAtualizar: unknown[] = [];

            // Título (se enviado)
            if (title !== undefined) {
                if (!tituloValido(title)) {
                    throw new Error("O título da tarefa deve conter pelo menos 3 caracteres válidos.");
                }
                camposParaAtualizar.push("titulo = ?");
                valoresParaAtualizar.push(title.trim());
            }

            // Prioridade (se enviada)
            if (prioridade !== undefined) {
                if (!PRIORIDADES.includes(prioridade as typeof PRIORIDADES[number])) {
                    throw new Error("Prioridade inválida. Use 'low', 'medium' ou 'high'.");
                }
                camposParaAtualizar.push("prioridade = ?");
                valoresParaAtualizar.push(prioridade);
            }

            // Status (se enviado)
            if (status !== undefined) {
                if (!STATUS_VALIDOS.includes(status as typeof STATUS_VALIDOS[number])) {
                    throw new Error("Status inválido. Use 'pending' ou 'completed'.");
                }
                camposParaAtualizar.push("status = ?");
                valoresParaAtualizar.push(status);
            }

            if (camposParaAtualizar.length === 0) return tarefaExistente;

            // Query dinâmica SEGURA: placeholders ? + valores array
            const sql = `UPDATE tarefas SET ${camposParaAtualizar.join(", ")} WHERE id = ?`;
            valoresParaAtualizar.push(idParaAtualizar);

            db.prepare(sql).run(...valoresParaAtualizar);
            return stmtBuscarPorId.get(idParaAtualizar) as Tarefa;
        });

        const resultado = fluxoAtualizacao();

        if (!resultado) {
            return res.status(404).json({ message: "Tarefa não encontrada para atualização parcial!" });
        }

        return res.status(200).json(resultado);
    } catch (erro) {
        // Distingue erro de validação (400) de erro interno (500)
        if (erro instanceof Error &&
            (erro.message.includes("inválid") || erro.message.includes("caracteres"))) {
            return res.status(400).json({ error: erro.message });
        }
        return res.status(500).json({ error: "Erro ao processar a atualização parcial no banco." });
    }
});

// Inicia o servidor
app.listen(PORT, () => {
    console.log(`Servidor rodando em: http://localhost:${PORT}`);
});
