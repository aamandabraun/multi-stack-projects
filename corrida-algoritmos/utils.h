#ifndef UTILS_H
#define UTILS_H

#include "aluno.h"

// contadores globais
extern int comparacoes;
extern int trocas;

// controle
void resetarContadores();

// util
void trocar(Aluno *a, Aluno *b);

// geração de dados
void gerarAleatorio(Aluno v[], int n);
void gerarOrdenado(Aluno v[], int n);
void gerarInverso(Aluno v[], int n);

// saída
void imprimir(Aluno v[], int n);

#endif