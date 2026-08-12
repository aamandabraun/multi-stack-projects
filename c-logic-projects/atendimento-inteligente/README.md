# Sistema de Atendimentos Técnicos

Trabalho de Estruturas de Dados em C — gerenciamento de atendimentos técnicos com fila dinâmica, lista encadeada, árvore BST, tabela hash e ordenação.

---

## Índice

1. [Compilação e Execução](#compilação-e-execução)
2. [Estrutura do Projeto](#estrutura-do-projeto)
3. [Menu do Sistema](#menu-do-sistema)
4. [Estruturas de Dados Utilizadas](#estruturas-de-dados-utilizadas)
5. [Requisitos Atendidos](#requisitos-atendidos)

---

## Compilação e Execução

### Linux / macOS

```bash
gcc main.c atendimento.c fila.c lista.c arvore.c hash.c ordenacao.c estatisticas.c -o sistema
./sistema
```

### Windows (MinGW / GCC)

```bash
gcc main.c atendimento.c fila.c lista.c arvore.c hash.c ordenacao.c estatisticas.c -o sistema.exe
sistema.exe
```

> **Requisito:** GCC instalado. No Ubuntu/Debian: `sudo apt install gcc`

### Compilação com verificação de memória (opcional)

```bash
gcc main.c atendimento.c fila.c lista.c arvore.c hash.c ordenacao.c estatisticas.c \
    -o sistema -Wall -Wextra -fsanitize=address,undefined
./sistema
```

---

## Estrutura do Projeto

```
projeto-estruturas-dados/
├── README.md
├── main.c              # Ponto de entrada e menu do sistema
├── atendimento.h/c     # TAD Atendimento — estrutura base
├── fila.h/c            # TAD Fila Dinâmica (FIFO)
├── lista.h/c           # TAD Lista Encadeada (histórico)
├── arvore.h/c          # TAD Árvore Binária de Busca (BST)
├── hash.h/c            # TAD Tabela Hash com chaining
├── ordenacao.h/c       # Algoritmos de ordenação (Bubble Sort)
└── estatisticas.h/c    # Estatísticas e persistência em CSV
```

**Persistência:** ao sair, o sistema salva automaticamente `atendimentos.csv`. Na próxima execução, os dados são carregados automaticamente.

---

## Menu do Sistema

```
===== SISTEMA DE ATENDIMENTOS TECNICOS =====
  Fila: X | Historico: Y
--------------------------------------------
  1  - Cadastrar atendimento
  2  - Atender proximo da fila
  3  - Cancelar atendimento
  4  - Listar fila de espera
  5  - Listar historico
  6  - Buscar por nome do cliente        (busca parcial, case-insensitive)
  7  - Buscar por prioridade
  8  - Buscar por ID (arvore BST)        [avancado]
  9  - Buscar por categoria (hash)       [avancado]
  10 - Ordenar historico por prioridade
  11 - Ordenar historico por tempo estimado
  12 - Ordenar por prioridade + tempo    (multiplos criterios)
  13 - Exibir estatisticas               [avancado]
  14 - Salvar historico em arquivo       [extra]
  15 - Gerar atendimentos de teste       [extra]
  0  - Sair
```

---

## Estruturas de Dados Utilizadas

### Fila Dinâmica (FIFO) — `fila.h/c`

Controla a **ordem de atendimento**. Cada chamado ao suporte entra no final da fila e é processado da frente. Implementada com **lista encadeada dinâmica** (sem vetor fixo), permitindo crescimento ilimitado.

- `enfileirar`: O(1) — inserção no `tras`
- `desenfileirar`: O(1) — remoção do `frente`
- Vantagem sobre vetor: sem desperdício de espaço e sem limite fixo

### Lista Encadeada — `lista.h/c`

Mantém o **histórico completo** de todos os atendimentos cadastrados. Cada nó aloca memória independente.

- Inserção: O(n) — insere no final para manter ordem cronológica
- Busca sequencial: O(n) — percorre todos os nós
- Vantagem: mantém a ordem de inserção e permite percorrer todos os registros

### Árvore Binária de Busca (BST) — `arvore.h/c`

Permite **busca rápida por ID** em O(log n) médio. Cada inserção compara o ID com a raiz e desce para a subárvore correta. Inclui remoção com três casos (sem filhos, um filho, dois filhos com sucessor in-order).

- Busca: O(log n) médio, O(n) pior caso (árvore degenerada)
- Vantagem sobre busca na lista: muito mais rápido para IDs em conjuntos grandes

### Tabela Hash — `hash.h/c`

Agrupa atendimentos por **categoria**. Usa a função djb2 para mapear a string da categoria a um índice de 0 a 12 (tamanho primo = 13). Colisões resolvidas por **encadeamento separado** (chaining).

- Busca por categoria: O(1) médio
- Função djb2: `hash = hash * 33 + c` — excelente distribuição para strings curtas
- Vantagem: busca por categoria praticamente instantânea

### Ordenação — `ordenacao.h/c`

Implementa **Bubble Sort** sobre os dados dos nós da lista encadeada (troca os dados sem remanejar ponteiros). Suporta três modos:

- Por prioridade (alta → baixa)
- Por tempo estimado (menor → maior)
- Por ambos (prioridade alta primeiro; empate desempata pelo menor tempo)

---

## Requisitos Atendidos

### Obrigatórios ✅

| # | Requisito | Implementação |
|---|-----------|---------------|
| 1 | Cadastrar atendimentos | `acao_cadastrar()` em `main.c` |
| 2 | Fila dinâmica | `fila.h/c` — FIFO com alocação dinâmica |
| 3 | Lista encadeada (histórico) | `lista.h/c` |
| 4 | Atender próximo da fila | `acao_atender_proximo()` |
| 5 | Listar fila de espera | `fila_listar()` |
| 6 | Listar histórico | `lista_listar()` |
| 7 | Busca sequencial | `lista_buscar_por_cliente()`, `lista_buscar_por_prioridade()` |
| 8 | Ordenação | `ordenacao.h/c` — por prioridade e tempo |
| 9 | Código modular em `.h/.c` | Todos os TADs separados |
| 10 | Menu funcional | `main.c` com 15 opções |
| 11 | README.md | Este arquivo |
| 12 | Git com commits | Histórico com 10 commits distribuídos |

### Avançados ✅

| # | Requisito | Implementação |
|---|-----------|---------------|
| A | Árvore BST por ID | `arvore.h/c` com remoção |
| B | Tabela Hash por categoria | `hash.h/c` com djb2 + chaining |
| C | Estatísticas do sistema | `estatisticas_exibir()` |
| D | Liberação de memória | `_destruir()` em todos os TADs |
| E | Responsabilidades separadas | Nenhuma lógica de negócio no `main.c` |

### Extras ✅

| # | Item | Implementação |
|---|------|---------------|
| 1 | Salvar/carregar CSV | `arquivo_salvar()`, `arquivo_carregar()` |
| 2 | Geração automática de testes | `acao_gerar_testes()` |
| 3 | Remoção na árvore BST | `arvore_remover()` |
| 4 | Busca parcial por nome | `lista_buscar_por_cliente()` com `strstr` |
| 5 | Ordenação por múltiplos critérios | `ordenar_por_prioridade_e_tempo()` |
| 6 | Categoria com mais atendimentos | `hash_categoria_mais_atendimentos()` |
| 7 | Cancelar atendimento | `acao_cancelar()` |
| 8 | Validação de entradas | `ler_int()` com intervalo em `main.c` |


> **Nota:** Ambos os integrantes devem compreender o sistema completo,
> pois qualquer pergunta pode ser direcionada a qualquer membro na apresentação.
