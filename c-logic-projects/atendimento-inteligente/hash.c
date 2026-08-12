#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hash.h"

/* =============================================
   Implementação da Tabela Hash com Chaining
   ============================================= */

/* Função hash: djb2 sobre a string da categoria */
static unsigned int hash_funcao(const char *chave)
{
    unsigned long hash = 5381;
    int c;
    while ((c = (unsigned char)*chave++))
        hash = ((hash << 5) + hash) + tolower(c);
    return (unsigned int)(hash % HASH_TAMANHO);
}

void hash_inicializar(Hash *h)
{
    int i;
    for (i = 0; i < HASH_TAMANHO; i++)
        h->baldes[i] = NULL;
    h->total = 0;
}

int hash_inserir(Hash *h, Atendimento a)
{
    unsigned int idx = hash_funcao(a.categoria);
    NoBalde *novo = (NoBalde *)malloc(sizeof(NoBalde));
    if (!novo) {
        fprintf(stderr, "Erro: falha ao alocar balde da hash.\n");
        return 0;
    }
    novo->dado     = a;
    novo->proximo  = h->baldes[idx];
    h->baldes[idx] = novo;
    h->total++;
    return 1;
}

int hash_buscar_por_categoria(const Hash *h, const char *categoria)
{
    unsigned int idx = hash_funcao(categoria);
    NoBalde *atual   = h->baldes[idx];
    int encontrados  = 0;

    while (atual) {
        if (strcasecmp(atual->dado.categoria, categoria) == 0) {
            atendimento_exibir(&atual->dado);
            encontrados++;
        }
        atual = atual->proximo;
    }
    return encontrados;
}

void hash_listar_tudo(const Hash *h)
{
    int i, algum = 0;
    for (i = 0; i < HASH_TAMANHO; i++) {
        NoBalde *atual = h->baldes[i];
        while (atual) {
            atendimento_exibir(&atual->dado);
            algum = 1;
            atual = atual->proximo;
        }
    }
    if (!algum) printf("  [Hash vazia]\n");
}

void hash_categoria_mais_atendimentos(const Hash *h)
{
    char categorias[HASH_TAMANHO * 10][30];
    int  contagens[HASH_TAMANHO * 10];
    int  num_cats = 0;
    int  i;

    for (i = 0; i < HASH_TAMANHO; i++) {
        NoBalde *atual = h->baldes[i];
        while (atual) {
            int j, achou = 0;
            for (j = 0; j < num_cats; j++) {
                if (strcasecmp(categorias[j], atual->dado.categoria) == 0) {
                    contagens[j]++;
                    achou = 1;
                    break;
                }
            }
            if (!achou) {
                strncpy(categorias[num_cats], atual->dado.categoria, 29);
                categorias[num_cats][29] = '\0';
                contagens[num_cats]      = 1;
                num_cats++;
            }
            atual = atual->proximo;
        }
    }

    if (num_cats == 0) {
        printf("  Nenhuma categoria encontrada.\n");
        return;
    }

    int idx_max = 0;
    for (i = 1; i < num_cats; i++)
        if (contagens[i] > contagens[idx_max]) idx_max = i;

    printf("  Categoria com mais atendimentos: %s (%d atendimento(s))\n",
           categorias[idx_max], contagens[idx_max]);
}

int hash_atualizar_status(Hash *h, int id, const char *novo_status)
{
    int i;
    for (i = 0; i < HASH_TAMANHO; i++) {
        NoBalde *atual = h->baldes[i];
        while (atual) {
            if (atual->dado.id == id) {
                strncpy(atual->dado.status, novo_status,
                        sizeof(atual->dado.status) - 1);
                atual->dado.status[sizeof(atual->dado.status) - 1] = '\0';
                return 1;
            }
            atual = atual->proximo;
        }
    }
    return 0;
}

void hash_destruir(Hash *h)
{
    int i;
    for (i = 0; i < HASH_TAMANHO; i++) {
        NoBalde *atual = h->baldes[i];
        while (atual) {
            NoBalde *prox = atual->proximo;
            free(atual);
            atual = prox;
        }
        h->baldes[i] = NULL;
    }
    h->total = 0;
}
