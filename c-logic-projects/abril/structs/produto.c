#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    float preco;
} Produto;

void criar_produto() {
    Produto *p = (Produto *) malloc(sizeof(Produto));
    if (p != NULL) {
        p->id = 101;   
        p->preco = 29.90;  
        printf("Produto %d: R$ %.2f\n", p->id, p->preco);
        free(p);
    }
}