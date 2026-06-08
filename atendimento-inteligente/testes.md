# Testes do Sistema

## Ambiente
- Compilador: GCC
- Flags: -Wall -Wextra -fsanitize=address,undefined
- Sistema: Linux/Windows

## Comando de Compilação
```bash
gcc main.c atendimento.c fila.c lista.c arvore.c hash.c ordenacao.c estatisticas.c -o sistema -Wall -Wextra
```

## Casos Testados

| # | Ação | Entrada | Resultado Esperado | OK? |
|---|------|---------|-------------------|-----|
| 1 | Cadastrar atendimento | Nome: Ana, Cat: Hardware, Prio: 3, Tempo: 30 | ID #1 criado, aparece na fila e histórico | ✅ |
| 2 | Atender próximo | - | Status muda para "atendido", sai da fila | ✅ |
| 3 | Cancelar atendimento | ID: 1 | Status muda para "cancelado" | ✅ |
| 4 | Listar fila vazia | - | Mensagem "[Fila de espera vazia]" | ✅ |
| 5 | Busca por nome parcial | "ana" | Encontra "Ana Lima" e "Mariana" | ✅ |
| 6 | Busca por prioridade | 3 | Lista só os de prioridade Alta | ✅ |
| 7 | Busca por ID na BST | ID: 2 | Retorna atendimento correto em O(log n) | ✅ |
| 8 | Busca por categoria na Hash | "Software" | Lista todos da categoria | ✅ |
| 9 | Ordenar por prioridade | - | Alta aparece primeiro | ✅ |
| 10 | Ordenar por tempo | - | Menor tempo aparece primeiro | ✅ |
| 11 | Estatísticas | - | Totais e contagens corretos | ✅ |
| 12 | Salvar CSV e recarregar | - | Dados persistem entre execuções | ✅ |
| 13 | Gerar testes automáticos | 5 | 5 atendimentos criados aleatoriamente | ✅ |
| 14 | Memória (sanitizer) | - | Nenhum leak detectado ao sair | ✅ |

## Resultado
Todos os fluxos aprovados. Nenhum warning de compilação.