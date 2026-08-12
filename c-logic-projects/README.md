# 🔵 C: Lógica de Programação e Estruturas Dinâmicas

> Repositório dedicado ao estudo da linguagem C, focado em algoritmos de baixo nível, manipulação direta de memória e tipos heterogêneos, desenvolvidos durante a graduação de ADS.

---

## 🚀 Tecnologias e Ferramentas

- **Linguagem:** C (Padrão C11/C17)
- **Ambiente:** VS Code + GCC (MinGW)
- **Paradigma:** Imperativo e Estruturado

## 📘 Conteúdos Praticados

Atualmente, o repositório cobre:

- **Gerenciamento de Memória:** Alocação dinâmica com `malloc`, `realloc` e `free`.
- **Ponteiros:** Aritmética de ponteiros, passagens por referência e ponteiros de ponteiros.
- **Estruturas de Dados:** Implementação de `structs` dinâmicas e gerenciamento de registros (Entidades).
- **Modularização:** Organização de código em arquivos de cabeçalho (`.h`) e implementação (`.c`).
- **Algoritmos Avançados:** Busca sequencial, filtragem de dados e análise de complexidade Big O.
- **Estruturas de Dados Avançadas:** Fila dinâmica (FIFO), lista encadeada, árvore binária de busca (BST) e tabela hash com chaining.

## 📁 Estrutura do Repositório

O código está organizado por períodos de aprendizado, além de um projeto completo de estruturas de dados:

- **/fev**: Fundamentos de sintaxe, tipos primitivos e estruturas de controle.
- **/mar**: Introdução a vetores, strings e funções.
- **/abril**: Alocação dinâmica, structs avançadas e Tipos Abstratos de Dados (TAD).
- **/maio**: Árvores binárias de busca.
- **/jun**: Comparação de algoritmos de busca e aprofundamento em árvores binárias de busca.
- **/corrida-algoritmos**: Benchmark de ordenação (Bubble, Selection e Insertion Sort).
- **/atendimento-inteligente**: Sistema completo de atendimentos técnicos com fila dinâmica, lista encadeada, árvore BST, tabela hash e ordenação. [Ver detalhes ↓](#-projeto-em-destaque-sistema-de-atendimentos-técnicos)

---

## ⭐ Projeto em Destaque: Sistema de Atendimentos Técnicos

Trabalho de Estruturas de Dados em C — gerenciamento de atendimentos técnicos combinando cinco estruturas de dados clássicas em um único sistema funcional.

### Estruturas de Dados Utilizadas

| Estrutura | Uso no projeto | Complexidade |
|---|---|---|
| **Fila Dinâmica (FIFO)** | Ordem de atendimento — entra no final, sai da frente | O(1) enfileirar/desenfileirar |
| **Lista Encadeada** | Histórico completo de atendimentos | O(n) inserção/busca |
| **Árvore Binária de Busca (BST)** | Busca por ID, com remoção nos 3 casos clássicos | O(log n) médio |
| **Tabela Hash (chaining)** | Busca por categoria via função djb2 | O(1) médio |
| **Ordenação (Bubble Sort)** | Por prioridade, tempo estimado ou ambos | — |

### Compilação e execução

```bash
# Linux / macOS
gcc main.c atendimento.c fila.c lista.c arvore.c hash.c ordenacao.c estatisticas.c -o sistema
./sistema

# Windows (MinGW/GCC)
gcc main.c atendimento.c fila.c lista.c arvore.c hash.c ordenacao.c estatisticas.c -o sistema.exe
sistema.exe
```

### Funcionalidades

- Cadastro, atendimento e cancelamento de chamados
- Busca por nome (parcial), prioridade, ID (BST) e categoria (hash)
- Ordenação por prioridade, tempo estimado ou ambos
- Estatísticas do sistema e persistência automática em CSV
- Geração automática de dados de teste

### Estrutura interna

```
atendimento-inteligente/
├── main.c              # Ponto de entrada e menu do sistema
├── atendimento.h/c     # TAD Atendimento — estrutura base
├── fila.h/c            # TAD Fila Dinâmica (FIFO)
├── lista.h/c           # TAD Lista Encadeada (histórico)
├── arvore.h/c          # TAD Árvore Binária de Busca (BST)
├── hash.h/c            # TAD Tabela Hash com chaining
├── ordenacao.h/c       # Algoritmos de ordenação
└── estatisticas.h/c    # Estatísticas e persistência em CSV
```
