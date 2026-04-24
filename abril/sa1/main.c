#include "triagem.h"

int main() {
    DList *fila = criar_lista();
    
    Paciente p1 = {1, "Paciente A"};
    Paciente p2 = {2, "Paciente B"};
    Paciente p3 = {3, "Emergencia C"};

    inserir_triagem(fila, p1);
    inserir_triagem(fila, p2);
    inserir_emergencia(fila, p3);

    imprimir_auditoria(fila);

    remover_paciente_id(fila, 1);
    atender_paciente(fila);

    imprimir_auditoria(fila);

    return 0;
}