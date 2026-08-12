#include <stdio.h>

int main() {
    char nome[50];
    double salarioFixo, totalVendas, totalReceber;

    scanf("%s %lf %lf", nome, &salarioFixo, &totalVendas);

    totalReceber = salarioFixo + (totalVendas * 0.15);

    printf("TOTAL = R$ %.2f\n", totalReceber);

    return 0;
}