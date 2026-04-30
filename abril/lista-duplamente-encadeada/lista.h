#ifndef LISTA_H
#define LISTA_H

typedef struct Nodo {
    int valor;
    struct Nodo *anterior;
    struct Nodo *proximo;
} Nodo;

typedef struct Lista {
    Nodo *inicio;
    Nodo *fim;
    int tamanho;
} Lista;

Nodo* criar_nodo(int valor);
int obter_valor(Nodo *nodo);
void definir_valor(Nodo *nodo, int valor);
Nodo* obter_anterior(Nodo *nodo);
Nodo* obter_proximo(Nodo *nodo);
void definir_anterior(Nodo *nodo, Nodo *anterior);
void definir_proximo(Nodo *nodo, Nodo *proximo);
void destruir_nodo(Nodo *nodo);

Lista* criar_lista();
int esta_vazia(Lista *lista);
int tamanho_lista(Lista *lista);
void destruir_lista(Lista *lista);

int inserir_inicio(Lista *lista, int valor);
int inserir_fim(Lista *lista, int valor);
int inserir_posicao(Lista *lista, int valor, int posicao);

void imprimir_inicio_fim(Lista *lista);
void imprimir_fim_inicio(Lista *lista);

int remover_inicio(Lista *lista, int *valor_removido);
int remover_fim(Lista *lista, int *valor_removido);
int remover_valor(Lista *lista, int valor);

Nodo* buscar(Lista *lista, int valor);

#endif