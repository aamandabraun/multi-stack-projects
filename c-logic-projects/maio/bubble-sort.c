#include <stdio.h>
#include <string.h>

typedef struct {
    int codigo;
    char nome[50];
    char telefone[15];
} Cliente;

void ordenarPorCodigo(Cliente v[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (v[j].codigo > v[j + 1].codigo) {
                Cliente temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
}

void ordenarPorNome(Cliente v[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(v[j].nome, v[j + 1].nome) > 0) {
                Cliente temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
}

int buscaTelefone(Cliente v[], int n, char telBusca[]) {
    for (int i = 0; i < n; i++) {
        if (strcmp(v[i].telefone, telBusca) == 0) {
            return i; 
        }
    }
    return -1; 
}

void imprimirClientes(Cliente v[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Cod: %d | Nome: %-10s | Tel: %s\n", v[i].codigo, v[i].nome, v[i].telefone);
    }
    printf("-----------------------------\n");
}

int main() {
    Cliente lista[10] = {
        {50, "Zeca", "9999-1111"},
        {10, "Ana",  "8888-2222"},
        {30, "Beto", "7777-3333"},
        {20, "Duda", "6666-4444"},
        {40, "Caio", "5555-5555"},
        {90, "Yuri", "4444-6666"},
        {70, "Gabi", "3333-7777"},
        {60, "Hugo", "2222-8888"},
        {80, "Lia",  "1111-9999"},
        {100,"Mara", "0000-0000"}
    };

    printf("--- Lista Original (Desordenada) ---\n");
    imprimirClientes(lista, 10);

    ordenarPorCodigo(lista, 10);
    printf("--- Ordenado por CODIGO ---\n");
    imprimirClientes(lista, 10);

    ordenarPorNome(lista, 10);
    printf("--- Ordenado por NOME (Desafio) ---\n");
    imprimirClientes(lista, 10);

    char telProcurado[] = "5555-5555";
    int indice = buscaTelefone(lista, 10, telProcurado);

    if (indice != -1) {
        printf("Telefone %s encontrado! Cliente: %s\n", telProcurado, lista[indice].nome);
    } else {
        printf("Telefone nao encontrado.\n");
    }

    return 0;
}