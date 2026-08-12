#include <stdio.h>
#include <string.h>

#define TOTAL_CLIENTES 6

typedef struct {
    int codigo;
    char nome[50];
    char telefone[20];
} Cliente;

int buscar_cliente_por_codigo(Cliente clientes[], int tamanho, int codigo_busca) {
    for (int i = 0; i < tamanho; i++) {
        if (clientes[i].codigo == codigo_busca) {
            return i; 
        }
    }
    return -1; 
}

int buscar_cliente_por_nome(Cliente clientes[], int tamanho, char nome_busca[]) {
    for (int i = 0; i < tamanho; i++) {
        if (strcmp(clientes[i].nome, nome_busca) == 0) {
            return i;
        }
    }
    return -1;
}

int buscar_cliente_por_telefone(Cliente clientes[], int tamanho, char tel_busca[]) {
    for (int i = 0; i < tamanho; i++) {
        if (strcmp(clientes[i].telefone, tel_busca) == 0) {
            return i;
        }
    }
    return -1;
}

int main() {
    Cliente lista[TOTAL_CLIENTES] = {
        {101, "Ana",     "9999-0001"},
        {205, "Bruno",   "9999-0002"},
        {310, "Carla",   "9999-0003"},
        {412, "Diego",   "9999-0004"},
        {578, "Eduarda", "9999-0005"},
        {699, "Felipe",  "9999-0006"}
    };

    int pos;
    printf("--- Busca por Codigo ---\n");
    int cod_procurado = 412;
    pos = buscar_cliente_por_codigo(lista, TOTAL_CLIENTES, cod_procurado);
    
    if (pos != -1) {
        printf("Cliente encontrado por codigo: %s\n", lista[pos].nome);
    } else {
        printf("Cliente nao encontrado pelo codigo informado.\n");
    }

    printf("\n--- Busca por Nome ---\n");
    char nome_procurado[] = "Carla";
    pos = buscar_cliente_por_nome(lista, TOTAL_CLIENTES, nome_procurado);
    
    if (pos != -1) {
        printf("Cliente encontrado por nome: codigo %d\n", lista[pos].codigo);
    } else {
        printf("Cliente nao encontrado pelo nome informado.\n");
    }

    printf("\n--- Busca por Telefone ---\n");
    char tel_procurado[] = "9999-0005";
    pos = buscar_cliente_por_telefone(lista, TOTAL_CLIENTES, tel_procurado);
    
    if (pos != -1) {
        printf("Cliente encontrado por telefone: %s (Codigo: %d)\n", lista[pos].nome, lista[pos].codigo);
    } else {
        printf("Cliente nao encontrado pelo telefone informado.\n");
    }

    printf("\n--- Teste de Erro (Codigo Inexistente) ---\n");
    pos = buscar_cliente_por_codigo(lista, TOTAL_CLIENTES, 999);
    if (pos == -1) {
        printf("Cliente nao encontrado pelo codigo informado.\n");
    }

    return 0;
}