#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"

// ================= CONTADORES =================
int comparacoes = 0;
int trocas = 0;

// ================= CONTROLE =================
void resetarContadores() {
    comparacoes = 0;
    trocas = 0;
}

// ================= UTIL =================
void trocar(Aluno *a, Aluno *b) {
    Aluno temp = *a;
    *a = *b;
    *b = temp;
    trocas++;
}

// ================= GERADORES =================
void gerarAleatorio(Aluno v[], int n) {
    srand(time(NULL));

    for (int i = 0; i < n; i++) {
        v[i].matricula = i + 1;
        sprintf(v[i].nome, "Aluno %d", i + 1);
        v[i].nota = (rand() % 101) / 10.0; // 0.0 a 10.0
    }
}

void gerarOrdenado(Aluno v[], int n) {
    for (int i = 0; i < n; i++) {
        v[i].matricula = i + 1;
        sprintf(v[i].nome, "Aluno %d", i + 1);
        v[i].nota = i; // crescente
    }
}

void gerarInverso(Aluno v[], int n) {
    for (int i = 0; i < n; i++) {
        v[i].matricula = i + 1;
        sprintf(v[i].nome, "Aluno %d", i + 1);
        v[i].nota = n - i; // decrescente
    }
}

// ================= PRINT =================
void imprimir(Aluno v[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d | %s | %.1f\n", v[i].matricula, v[i].nome, v[i].nota);
    }
    printf("\n");
}