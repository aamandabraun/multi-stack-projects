#ifndef TRIAGEM_H
#define TRIAGEM_H

typedef struct Paciente {
    int id;
    char nome[50];
} Paciente;

typedef struct Node {
    Paciente dado;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct {
    Node *head;
    Node *tail;
    int size;
} DList;

DList* criar_lista();
void inserir_emergencia(DList *l, Paciente p);
void inserir_triagem(DList *l, Paciente p);
void atender_paciente(DList *l);
void remover_paciente_id(DList *l, int id);
void imprimir_auditoria(DList *l);

#endif