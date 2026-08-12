#include <stdio.h>
#include "estrutura.h"

int main() {
    Fila fila_atendimento;
    inicializar_fila(&fila_atendimento);

    Paciente p1 = {"Joao Silva", 101, "PROC_A"};
    Paciente p2 = {"Maria Oliveira", 102, "PROC_B"};

    inserir(&fila_atendimento, p1);
    inserir(&fila_atendimento, p2);

    printf("Pacientes em espera: %d\n", consultar_tamanho(&fila_atendimento));

    Paciente atendido;
    if (remover(&fila_atendimento, &atendido)) {
        printf("Atendendo agora: %s\n", atendido.nome);
    }

    printf("Fila atualizada: %d\n", consultar_tamanho(&fila_atendimento));

    limpar_fila(&fila_atendimento);
    return 0;
}