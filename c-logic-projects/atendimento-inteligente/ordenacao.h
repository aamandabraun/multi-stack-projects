#ifndef ORDENACAO_H
#define ORDENACAO_H

#include "lista.h"

/* =============================================
   TAD Ordenação
   Implementa Insertion Sort sobre a lista
   encadeada sem copiar para array auxiliar.
   Complexidade: O(n²) — adequada para listas
   de tamanho moderado de atendimentos.
   ============================================= */

void ordenar_por_prioridade(Lista *l);

void ordenar_por_tempo_estimado(Lista *l);

void ordenar_por_prioridade_e_tempo(Lista *l);

#endif 