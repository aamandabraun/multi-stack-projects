#include <stdio.h>

int main() {
    double valor;
    int notas[] = {100, 50, 20, 10, 5, 2};
    int moedas[] = {100, 50, 25, 10, 5, 1}; 
    
    if (scanf("%lf", &valor) != 1) return 0;

    int total_centavos = (int)(valor * 100 + 0.5);

    printf("NOTAS:\n");
    for (int i = 0; i < 6; i++) {
        int valor_nota_centavos = notas[i] * 100;
        int quantidade = total_centavos / valor_nota_centavos;
        printf("%d nota(s) de R$ %d.00\n", quantidade, notas[i]);
        total_centavos %= valor_nota_centavos;
    }

    printf("MOEDAS:\n");
    for (int i = 0; i < 6; i++) {
        int quantidade = total_centavos / moedas[i];
        printf("%d moeda(s) de R$ %.2f\n", quantidade, moedas[i] / 100.0);
        total_centavos %= moedas[i];
    }

    return 0;
}