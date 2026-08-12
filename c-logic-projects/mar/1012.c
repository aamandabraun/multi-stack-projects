#include <stdio.h>

int main() {
    double A, B, C;
    double TRIANGULO, CIRCULO, TRAPEZIO, QUADRADO, RETANGULO;
    double pi = 3.14159;

    scanf("%lf %lf %lf", &A, &B, &C);

    TRIANGULO = (A * C) / 2.0;
    CIRCULO = pi * (C * C);
    TRAPEZIO = ((A + B) * C) / 2.0;
    QUADRADO = B * B;
    RETANGULO = A * B;

    printf("TRIANGULO: %.3f\n", TRIANGULO);
    printf("CIRCULO: %.3f\n", CIRCULO);
    printf("TRAPEZIO: %.3f\n", TRAPEZIO);
    printf("QUADRADO: %.3f\n", QUADRADO);
    printf("RETANGULO: %.3f\n", RETANGULO);

    return 0;
}