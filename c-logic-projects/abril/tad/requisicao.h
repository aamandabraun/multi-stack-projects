#ifndef REQUISICAO_H
#define REQUISICAO_H

typedef struct {
    char nome[40];
    int codigo_inscricao;
    char codigo_procedimento[10];
} Paciente;

Paciente criar_paciente(const char* nome, int codigo, const char* proc);

#endif