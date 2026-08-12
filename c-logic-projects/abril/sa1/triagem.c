#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "triagem.h"

DList* criar_lista() {
    DList *l = (DList*) malloc(sizeof(DList));
    l->head = l->tail = NULL;
    l->size = 0;
    return l;
}

void inserir_emergencia(DList *l, Paciente p) {
    Node *novo = (Node*) malloc(sizeof(Node));
    novo->dado = p;
    novo->next = l->head;
    novo->prev = NULL;

    if (l->head == NULL) {
        l->tail = novo;
    } else {
        l->head->prev = novo;
    }
    l->head = novo;
    l->size++;
}

void inserir_triagem(DList *l, Paciente p) {
    Node *novo = (Node*) malloc(sizeof(Node));
    novo->dado = p;
    novo->next = NULL;
    novo->prev = l->tail;

    if (l->tail == NULL) {
        l->head = novo;
    } else {
        l->tail->next = novo;
    }
    l->tail = novo;
    l->size++;
}

void atender_paciente(DList *l) {
    if (l->head == NULL) return;

    Node *aux = l->head;
    l->head = l->head->next;

    if (l->head != NULL) {
        l->head->prev = NULL;
    } else {
        l->tail = NULL;
    }

    free(aux);
    l->size--;
}

void remover_paciente_id(DList *l, int id) {
    Node *aux = l->head;
    
    while (aux != NULL && aux->dado.id != id) {
        aux = aux->next;
    }

    if (aux == NULL) return;

    if (aux == l->head) {
        l->head = aux->next;
    } else {
        aux->prev->next = aux->next;
    }

    if (aux == l->tail) {
        l->tail = aux->prev;
    } else {
        aux->next->prev = aux->prev;
    }

    free(aux);
    l->size--;
}

void imprimir_auditoria(DList *l) {
    Node *aux;
    printf("\n--- Auditoria (Início -> Fim) ---\n");
    aux = l->head;
    while (aux != NULL) {
        printf("ID: %d | Nome: %s\n", aux->dado.id, aux->dado.nome);
        aux = aux->next;
    }

    printf("\n--- Auditoria (Fim -> Início) ---\n");
    aux = l->tail;
    while (aux != NULL) {
        printf("ID: %d | Nome: %s\n", aux->dado.id, aux->dado.nome);
        aux = aux->prev;
    }
}