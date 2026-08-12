#include <stdio.h>

typedef struct {
    char nome[50];
    float nota;
} Aluno;

void vetor_alunos() {
    Aluno *turma = (Aluno *) malloc(3 * sizeof(Aluno));
    
    if (turma != NULL) {
        turma[0].nota = 8.5;
        free(turma);
    }
}