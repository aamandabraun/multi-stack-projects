#include <stdio.h>
#include <string.h>
#include "atendimento.h"

/* =============================================
   Implementação do TAD Atendimento
   ============================================= */

Atendimento atendimento_criar(int id,
                               const char *cliente,
                               const char *categoria,
                               int prioridade,
                               int tempo_estimado)
{
    Atendimento a;
    a.id = id;
    strncpy(a.cliente,    cliente,    sizeof(a.cliente)    - 1);
    strncpy(a.categoria,  categoria,  sizeof(a.categoria)  - 1);
    a.cliente[sizeof(a.cliente) - 1]   = '\0';
    a.categoria[sizeof(a.categoria) - 1] = '\0';
    a.prioridade     = prioridade;
    a.tempo_estimado = tempo_estimado;
    strncpy(a.status, "aberto", sizeof(a.status) - 1);
    a.status[sizeof(a.status) - 1] = '\0';
    return a;
}

const char *atendimento_prioridade_str(int prioridade)
{
    switch (prioridade) {
        case 1:  return "Baixa";
        case 2:  return "Media";
        case 3:  return "Alta";
        default: return "Desconhecida";
    }
}

void atendimento_exibir(const Atendimento *a)
{
    printf("  ID          : %d\n",  a->id);
    printf("  Cliente     : %s\n",  a->cliente);
    printf("  Categoria   : %s\n",  a->categoria);
    printf("  Prioridade  : %s\n",  atendimento_prioridade_str(a->prioridade));
    printf("  Tempo Est.  : %d min\n", a->tempo_estimado);
    printf("  Status      : %s\n",  a->status);
    printf("  ----------------------------\n");
}