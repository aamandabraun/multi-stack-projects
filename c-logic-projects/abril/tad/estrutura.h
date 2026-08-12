#ifndef ESTRUTURA_H
#define ESTRUTURA_H

#include "requisicao.h"

typedef struct No {
    Paciente dado;
    struct No* proximo;
} No;

typedef struct {
    No* inicio;
    No* fim;
    int tamanho;
} Fila;

void inicializar_fila(Fila* f);
int inserir(Fila* f, Paciente p);
int remover(Fila* f, Paciente* p_saida);
int consultar_tamanho(Fila* f);
void limpar_fila(Fila* f);

#endif