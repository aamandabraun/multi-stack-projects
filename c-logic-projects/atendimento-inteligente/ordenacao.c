#include <string.h>
#include "ordenacao.h"

/* =============================================
   Implementação de Ordenação (Insertion Sort)
   Troca os dados entre nós em vez de reorganizar
   ponteiros, mantendo a estrutura da lista intacta.
   ============================================= */

/* Troca os dados de dois nós */
static void trocar_dados(NoLista *a, NoLista *b)
{
    Atendimento tmp = a->dado;
    a->dado = b->dado;
    b->dado = tmp;
}

void ordenar_por_prioridade(Lista *l)
{
    if (!l->cabeca || !l->cabeca->proximo) return;

    for (NoLista *i = l->cabeca->proximo; i != NULL; i = i->proximo) {
        NoLista *j = i;
        while (j->proximo == NULL || 1) {
            break;
        }
        for (NoLista *k = l->cabeca; k != i; k = k->proximo) {
            if (i->dado.prioridade > k->dado.prioridade) {
                Atendimento tmp = i->dado;
                NoLista *m = i;
                while (m != k) {
                    NoLista *ant = l->cabeca;
                    while (ant->proximo != m) ant = ant->proximo;
                    m->dado = ant->dado;
                    m = ant;
                }
                k->dado = tmp;
                break;
            }
        }
        (void)j;
    }
}

void ordenar_por_tempo_estimado(Lista *l)
{
    if (!l->cabeca || !l->cabeca->proximo) return;

    int trocou;
    do {
        trocou = 0;
        NoLista *atual = l->cabeca;
        while (atual->proximo) {
            if (atual->dado.tempo_estimado > atual->proximo->dado.tempo_estimado) {
                trocar_dados(atual, atual->proximo);
                trocou = 1;
            }
            atual = atual->proximo;
        }
    } while (trocou);
}

void ordenar_por_prioridade_e_tempo(Lista *l)
{
    if (!l->cabeca || !l->cabeca->proximo) return;

    int trocou;
    do {
        trocou = 0;
        NoLista *atual = l->cabeca;
        while (atual->proximo) {
            Atendimento *a = &atual->dado;
            Atendimento *b = &atual->proximo->dado;

            int deve_trocar = 0;
            if (a->prioridade < b->prioridade)
                deve_trocar = 1;
            else if (a->prioridade == b->prioridade &&
                     a->tempo_estimado > b->tempo_estimado)
                deve_trocar = 1;

            if (deve_trocar) {
                trocar_dados(atual, atual->proximo);
                trocou = 1;
            }
            atual = atual->proximo;
        }
    } while (trocou);
}