#include <stdio.h>
#include <stdlib.h> 

int main() {
    int a, b, c, maiorAB, maiorFinal;

    if (scanf("%d %d %d", &a, &b, &c) != 3) return 0;

    maiorAB = (a + b + abs(a - b)) / 2;
    maiorFinal = (maiorAB + c + abs(maiorAB - c)) / 2;

    printf("%d eh o maior\n", maiorFinal);

    return 0;
}