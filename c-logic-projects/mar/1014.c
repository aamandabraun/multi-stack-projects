#include <stdio.h>

int main() {
    int X;         
    double Y;      
    double consumo;

    if (scanf("%d %lf", &X, &Y) != 2) return 0;
    consumo = X / Y;

    printf("%.3f km/l\n", consumo);

    return 0;
}