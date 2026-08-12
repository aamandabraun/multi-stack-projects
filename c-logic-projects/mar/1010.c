#include <stdio.h>

int main() {
    int cod1, qtd1, cod2, qtd2;
    double valor1, valor2, total;

    scanf("%d %d %lf", &cod1, &qtd1, &valor1);
    scanf("%d %d %lf", &cod2, &qtd2, &valor2);

    total = (qtd1 * valor1) + (qtd2 * valor2);

    printf("VALOR A PAGAR: R$ %.2f\n", total);

    return 0;
}