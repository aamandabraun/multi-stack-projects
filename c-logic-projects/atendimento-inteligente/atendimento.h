#ifndef ATENDIMENTO_H
#define ATENDIMENTO_H

/* =============================================
   TAD Atendimento
   Define a estrutura principal do sistema e
   funções auxiliares de criação e exibição.
   ============================================= */

typedef struct {
    int id;
    char cliente[50];
    char categoria[30];
    int prioridade;      
    int tempo_estimado; 
    char status[20];    
} Atendimento;

/* Cria e retorna um Atendimento preenchido */
Atendimento atendimento_criar(int id,
                               const char *cliente,
                               const char *categoria,
                               int prioridade,
                               int tempo_estimado);

void atendimento_exibir(const Atendimento *a);

const char *atendimento_prioridade_str(int prioridade);

#endif 