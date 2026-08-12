typedef struct {
    char rua[50];
} Endereco;

typedef struct {
    char nome[50];
    Endereco *end; 
} Pessoa;

void composicao() {
    Pessoa *p = (Pessoa *) malloc(sizeof(Pessoa));
    p->end = (Endereco *) malloc(sizeof(Endereco)); 

    strcpy(p->nome, "Amanda");
    strcpy(p->end->rua, "Av. Principal"); 

    printf("%s mora na %s\n", p->nome, p->end->rua);

    free(p->end); 
    free(p);  
}