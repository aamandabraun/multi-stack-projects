typedef struct {
    char *nome;
} Usuario;

void usuario_dinamico() {
    char buffer[100];
    printf("Digite o nome: ");
    scanf("%s", buffer);

    Usuario *u = (Usuario *) malloc(sizeof(Usuario));
    u->nome = (char *) malloc((strlen(buffer) + 1) * sizeof(char));
    
    strcpy(u->nome, buffer);
    printf("Usuario criado: %s\n", u->nome);
    
    free(u->nome); 
    free(u);  
}