#include <stdio.h>
#include <stdlib.h>

void alocacao_gigante() {
    size_t tamanho = 1024 * 1024 * 1024;
    char *ptr = (char *) malloc(tamanho);

    if (ptr == NULL) {
        printf("Erro: Memoria insuficiente para 1GB.\n");
    } else {
        printf("Sucesso! 1GB alocado.\n");
        free(ptr); 
    }
}