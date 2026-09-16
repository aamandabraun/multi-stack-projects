# Gerenciador de Tarefas - Sistema Web

## Visão Geral

Este projeto é um sistema web de gerenciamento de tarefas desenvolvido para praticar a criação de interfaces responsivas e a implementação de uma API REST com Node.js e Express.

A estrutura atual combina:

- front-end em HTML com Tailwind CSS
- backend em TypeScript
- API REST com Express para manipular tarefas
- persistência de tarefas em banco de dados SQLite
- validação de dados e consultas parametrizadas
- ambiente de desenvolvimento configurado com scripts para rodar e testar a aplicação

## Objetivo

Criar um gerenciador de tarefas funcional, com foco em:

- organização visual da interface
- cadastro e listagem de atividades
- estrutura inicial de API para integração com o front-end
- prática de desenvolvimento de sistemas web com rotas e manipulação de dados

## Status Atual do Projeto

As atualizações implementadas no commit mais recente incluem:

- criação do servidor Express em TypeScript
- configuração do projeto com scripts de desenvolvimento e build
- criação automática do banco `tarefas.db` e das tabelas `tarefas` e `usuarios`
- inserção de tarefas no SQLite por meio da rota `POST /api/tasks`
- validação do título, que é obrigatório e deve conter pelo menos 3 caracteres após a remoção de espaços
- suporte às prioridades `low`, `medium` e `high`, usando `medium` quando uma prioridade inválida não é informada
- busca de tarefas pelo parâmetro `search` com prepared statement
- exemplos de sucesso e de validação no arquivo `Aula_5e6/request.http`

## Tecnologias Utilizadas

- HTML5
- Tailwind CSS
- JavaScript/TypeScript
- Node.js
- Express
- TSX

## Estrutura do Projeto

```text
Gercenciador_Tarefas_Sistema_Web/
├── index.html                  # Interface principal do sistema
├── package.json                # Scripts e dependências do projeto
├── tailwind.config.js          # Configuração do Tailwind CSS
├── README.md                   # Documentação do projeto
├── tarefas.db                  # Banco de dados SQLite
├── Dicas e Truques.txt         # Anotações auxiliares
├── desafio_Aulas_3e4/          # Arquivos das aulas 3 e 4
│   └── Desafio_3e4.html
├── Aula_5e6/
│   ├── server.ts               # Servidor Express da aplicação
│   ├── request.http            # Exemplos de requisições HTTP
│   └── tsconfig.json           # Configuração do TypeScript
└── node_modules/               # Dependências instaladas
