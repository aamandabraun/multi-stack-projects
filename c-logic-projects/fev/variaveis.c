#include <stdio.h>

int main(){
    char numero1 = 1;
    int numero2 = 4;
    float numero3 = 4.2;
    double numero4 = 8;

    printf("char:   %zu byte(s)\n", sizeof(numero1));
    printf("int:   %zu byte(s)\n", sizeof(numero2));
    printf("float:   %zu byte(s)\n", sizeof(numero3));
    printf("double:   %zu byte(s)\n", sizeof(numero4));
    return 0;
}