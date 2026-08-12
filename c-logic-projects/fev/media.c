#include <stdio.h>

int main(){
    float nota1, nota2, nota3, media;

    printf("--- Calculadora de Media ---\n");
    printf("Digite a primeira nota: ");
    scanf("%f", &nota1);

    printf("Digite a segunda nota: ");
    scanf("%f", &nota2);

    printf("Digite a terceira nota: ");
    scanf("%f", &nota3);

    media = (nota1 + nota2 + nota3) / 3;
    printf("\nSua media final e: %.2f\n", media);

    if (media >= 6.0) {
        printf("Resultado: APROVADO!\n");
    } else {
        printf("Resultado: REPROVADO.\n");
    }

    return 0;
}