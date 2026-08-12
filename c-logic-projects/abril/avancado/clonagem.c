#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    float preco;
} Produto;

Produto* clonar(Produto *origem) {
    if (origem == NULL) return NULL;
    Produto *novo = (Produto *) malloc(sizeof(Produto));
}