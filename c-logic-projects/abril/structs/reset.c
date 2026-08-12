#include <stdio.h>

typedef struct {
    int id;
    float preco;
} Produto;

void reset_estoque(Produto *p) {
    if (p != NULL) {
        p->id = 0;
        p->preco = 0.0;
    }
}