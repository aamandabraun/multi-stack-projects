#include <stdio.h>

double media(double a, double b, double c);

int main(void){
    double n1, n2, n3, m;
    double numeros[5];
    double maior;
    char nome = Amanda;
    int idade;

    printf("Ola ", nome, "! Quantos anos voce tem?\n");
    if (idade >= 0) printf ("Ok");
    else printf("Numero invalido");

    printf("Digite suas 3 notas:\n");
    scanf("%f %f %f", &n1, &n2, &n3);
    m = media (n1, n2, n3);

    if (m >= 7.00) printf("Aprovado\n");
    else if (m >= 5.00) printf("Está em recuperação\n");
    else printf("Reprovado\n");

    printf("\nDigite os 5 numeros inteiros:\n");
        for(int i = 0; i < 5; i++){
            scanf("%d", &numeros[i]);
            if (i == 0 || numeros[i] > maior){
                maior = numeros[i];
            }
        }
    printf("O maior numero digitado foi: %d\n", maior);

    return 0;
}

double media(double a, double b, double c){
    return (a + b + c) / 3.00;
}