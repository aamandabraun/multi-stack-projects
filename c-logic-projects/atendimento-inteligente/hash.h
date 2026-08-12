#ifndef HASH_H
#define HASH_H

#include "atendimento.h"

/* =============================================
   TAD Tabela Hash
   Agrupa atendimentos por categoria usando
   encadeamento separado (chaining) para
   tratar colisões. Tamanho primo melhora
   distribuição.
   ============================================= */

#define HASH_TAMANHO 13   

typedef struct NoBalde {
    Atendimento dado;
    struct NoBalde *proximo;
} NoBalde;

typedef struct {
    NoBalde *baldes[HASH_TAMANHO];
    int total;
} Hash;

void hash_inicializar(Hash *h);

int hash_inserir(Hash *h, Atendimento a);


int hash_buscar_por_categoria(const Hash *h, const char *categoria);

void hash_listar_tudo(const Hash *h);

void hash_categoria_mais_atendimentos(const Hash *h);

int hash_atualizar_status(Hash *h, int id, const char *novo_status);

void hash_destruir(Hash *h);

#endif 
