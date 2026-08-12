#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No *proximo;
} No;

typedef struct{
    No *topo;
    int quantidade;
} Pilha;

void inicializar(Pilha *p){
    p -> topo = NULL;
    p -> quantidade = 0;
}

int push(Pilha *p, int valor){
    No *novo = (No *) malloc(sizeof(No));

    if (novo == NULL){
        printf("Sem memória disponível, libere espaço e tente novamente");
        return 0;
    }

    novo -> valor = valor;
    novo -> proximo = p -> topo;

    p -> topo = novo;
    p -> quantidade ++;
    return 1;
}

int pop(Pilha *p, int *valor){
    No *temp;

    if (p -> topo == NULL){
        printf("Pilha vazia, pulando pop");
            return 0;
    } 
}