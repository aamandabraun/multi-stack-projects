#include <stdio.h>
#include <stdlib.h>

int main() {
    float *ptr = (float *) malloc(sizeof(float));

    if (ptr == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    printf("Digite um valor float: \n");
    scanf("%f", ptr);

    printf("Valor digitado: %.2f\n", *ptr);

    free(ptr);
    return 0;
}