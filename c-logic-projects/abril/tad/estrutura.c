#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estrutura.h"

void inicializar_fila(Fila* f) {
    f->inicio = NULL;
    f->fim = NULL;
    f->tamanho = 0;
}

int inserir(Fila* f, Paciente p) {
    No* novo = (No*) malloc(sizeof(No));
    if (novo == NULL) return 0;

    novo->dado = p;
    novo->proximo = NULL;

    if (f->fim == NULL) {
        f->inicio = novo;
    } else {
        f->fim->proximo = novo;
    }
    
    f->fim = novo;
    f->tamanho++;
    return 1;
}

int remover(Fila* f, Paciente* p_saida) {
    if (f->inicio == NULL) return 0; 

    No* aux = f->inicio;
    *p_saida = aux->dado;
    
    f->inicio = f->inicio->proximo;
    
    if (f->inicio == NULL) {
        f->fim = NULL;
    }

    free(aux);
    f->tamanho--;
    return 1;
}

int consultar_tamanho(Fila* f) {
    return f->tamanho;
}

void limpar_fila(Fila* f) {
    Paciente descarte;
    while (remover(f, &descarte));
}