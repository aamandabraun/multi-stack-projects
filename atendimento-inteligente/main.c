typedef struct {
    int id;
    char cliente[50];
    char categoria[30];
    int prioridade;       // 1 = baixa, 2 = média, 3 = alta
    int tempo_estimado;   // em minutos
    char status[20];      // aberto, atendido ou cancelado
} Atendimento;