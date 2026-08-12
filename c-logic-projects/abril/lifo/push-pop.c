#include <stdio.h>
#define CAPACIDADE 5

int pilha[CAPACIDADE];
int topo = -1;

int push (int valor){
    if (topo == CAPACIDADE -1){
        printf("Capacidade excedida. Retornando");
        return 0;
    }

    pilha[++topo] = valor;
    return 1;
}
 
int main(){
    
    int removido;

    push(10);
    push(20);
    push(30);

    while(pop(&removido)){
        printf("Valor removido: %d\n", removido);
    }

    return 0;
}