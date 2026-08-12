#include <stdio.h>

#define FATOR 10

int main(){
    int numeroUsuario;

    printf("Multiplicador por fator %d ---\n", FATOR);
    printf("Digite um numero inteiro: ");
    scanf("%d", &numeroUsuario);
    int resultado = numeroUsuario * FATOR;

    printf("O resultado de %d x %d e: %d\n", numeroUsuario, FATOR, resultado);

    return 0;
}