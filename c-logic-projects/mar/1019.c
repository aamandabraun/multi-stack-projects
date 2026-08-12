#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);

    int horas = N / 3600;
    N %= 3600;
    
    int minutos = N / 60;
    int segundos = N % 60;

    printf("%d:%d:%d\n", horas, minutos, segundos);

    return 0;
}