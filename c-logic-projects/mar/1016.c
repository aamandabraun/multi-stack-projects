#include <stdio.h>

int main() {
    int distancia, tempo;

    if (scanf("%d", &distancia) != 1) return 0;
    tempo = distancia * 2;

    printf("%d minutos\n", tempo);

    return 0;
}