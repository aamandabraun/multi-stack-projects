#include <stdio.h>
#include "lista.h"

int main() {
    Lista *l = criar_lista();
    inserir_fim(l, 10);
    inserir_fim(l, 20);
    inserir_fim(l, 30);
    inserir_posicao(l, 15, 1);
    
    imprimir_inicio_fim(l);
    imprimir_fim_inicio(l);
    
    int r;
    remover_inicio(l, &r);
    remover_valor(l, 20);
    
    imprimir_inicio_fim(l);
    
    destruir_lista(l);
    return 0;
}