# 📝 Gerenciador de Tarefas

> Aplicação web para gerenciamento de tarefas, com front-end em HTML + Tailwind CSS e uma API REST segura em Express/TypeScript sobre SQLite.

<div align="center">

![Node.js](https://img.shields.io/badge/Node.js-20+-339933?style=for-the-badge&logo=node.js&logoColor=white)
![TypeScript](https://img.shields.io/badge/TypeScript-5+-3178C6?style=for-the-badge&logo=typescript&logoColor=white)
![Express](https://img.shields.io/badge/Express-5+-000000?style=for-the-badge&logo=express&logoColor=white)
![SQLite](https://img.shields.io/badge/SQLite-3-003B57?style=for-the-badge&logo=sqlite&logoColor=white)

</div>

---

## 📖 Sobre o projeto

O **Gerenciador de Tarefas** é uma aplicação para cadastro, consulta, atualização e exclusão de tarefas, com prioridade e status configuráveis.

A tela principal (`index.html`) oferece uma interface simples de acesso e listagem, enquanto o back-end expõe uma API REST completa, com foco em:

- 🌐 CRUD completo (GET, POST, PUT, PATCH e DELETE)
- 🔐 Segurança contra SQL Injection com Prepared Statements
- ✅ Validação centralizada em helpers reutilizáveis (type guards e allowlists)
- 🔄 Transações para garantir atualizações parciais atômicas
- 🧪 Testes de endpoints via REST Client

---

## 🎯 Objetivos

O projeto tem como principais objetivos:

- Implementar uma API REST funcional para tarefas;
- Validar rigorosamente os dados recebidos (título, prioridade e status);
- Padronizar a validação de IDs e a criação de queries dinâmicas seguras;
- Garantir atomicidade em atualizações parciais com `db.transaction`;
- Diferenciar erros de validação (400) de erros internos (500), sem vazar detalhes do banco;
- Praticar organização de rotas Express com TypeScript.

---

## 🛠️ Tecnologias utilizadas

| Tecnologia | Utilização |
|---|---|
| 🟢 **Node.js** | Ambiente de execução |
| 🔷 **TypeScript** | Linguagem de programação |
| ⚫ **Express** | Criação da API REST |
| 🗃️ **SQLite** | Banco de dados |
| 🔒 **better-sqlite3** | Comunicação com SQLite |
| 🎨 **Tailwind CSS** | Estilização da interface |
| 🧪 **REST Client** | Testes da API |

---

## 📚 Modelo de dados

A entidade principal da aplicação é a **Tarefa**:

```text
┌─────────────────────────────┐
│           TAREFA            │
├─────────────────────────────┤
│ id          → INTEGER       │
│ titulo      → TEXT          │
│ prioridade  → TEXT          │ (low | medium | high)
│ status      → TEXT          │ (pending | completed)
└─────────────────────────────┘
```

---

## 🔌 Endpoints

| Método | Rota | Descrição |
|---|---|---|
| `GET` | `/api/tasks` | Lista todas as tarefas (aceita `?search=` para busca por título) |
| `POST` | `/api/tasks` | Cria uma nova tarefa |
| `PUT` | `/api/tasks/:id` | Atualiza uma tarefa por completo |
| `PATCH` | `/api/tasks/:id` | Atualiza campos específicos de uma tarefa (transacional) |
| `DELETE` | `/api/tasks/:id` | Remove uma tarefa |

---

## 📁 Estrutura do projeto

```text
Gerenciador_Tarefas/
├── index.html              # Tela principal do sistema
├── server.ts               # API Express (rotas, validações e transações)
├── request.http            # Coleção de testes via REST Client
├── package.json            # Scripts e dependências
├── tsconfig.json           # Configuração do TypeScript
├── tailwind.config.js      # Configuração do Tailwind CSS
├── tarefas.db              # Banco de dados SQLite
└── desafio_Aulas_3e4/      # Exercícios das aulas 3 e 4
```

---

## ▶️ Como rodar

```bash
npm install
npm run dev
```

O servidor sobe em `http://localhost:3000` (ou na porta definida em `process.env.PORT`).
