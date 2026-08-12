#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char nome[50];
    float nota;
} Aluno;

Aluno** filtrar_aprovados(Aluno *turma, int total, int *qtd_aprovados) {
    Aluno **aprovados = (Aluno **) malloc(total * sizeof(Aluno *));
}