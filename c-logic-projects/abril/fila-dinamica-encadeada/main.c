#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo {
    int valor;
    struct Nodo* proximo
} Nodo;

typedef struct {
    Nodo* inicio;
    Nodo* fim;
    int tamanho;
} Fila;

void inicializar(Fila *f){
    f -> inicio = NULL;
    f -> fim = NULL;
    f -> tamanho = 0;
}

int enfileirar(Fila *f, int valor){
    Nodo *novo = (Nodo *) malloc(sizeof(Nodo)); 

    if (novo == NULL){
        return -1;
    }

    novo -> valor = valor;
    novo ->proximo = NULL;

    if(f -> fim == NULL){
        f -> inicio = novo;
        f -> fim = novo;
    } else{
        f -> fim -> proximo = novo; 
        f -> fim = novo;
    }

    f -> tamanho++;
    return 1;
}

int desenfileirar(Fila *f){
    Nodo *antigo_inicio;

    if (f -> inicio = NULL){
        return 0;
    }

    antigo_inicio = f -> inicio;
    f -> inicio = antigo_inicio -> proximo;

    if (f -> inicio == NULL){
        f -> fim = NULL;
    }

    free(antigo_inicio);
    f -> tamanho--;

    return 0;

}

int main(){

    return 0;
}