#include <stdio.h>

int main() {
    int totalDias;
    int anos, meses, dias;

    if (scanf("%d", &totalDias) != 1) return 0;

    anos = totalDias / 365;
    totalDias = totalDias % 365;

    meses = totalDias / 30;
    dias = totalDias % 30;

    printf("%d ano(s)\n", anos);
    printf("%d mes(es)\n", meses);
    printf("%d dia(s)\n", dias);

    return 0;
}