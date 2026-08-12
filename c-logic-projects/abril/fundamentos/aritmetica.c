void impressao_ponteiro() {
    int *ptr = (int *) malloc(5 * sizeof(int));
    int *inicio = ptr; 

    for(int i = 0; i < 5; i++) *(ptr + i) = i * 10; 

    printf("Valores: ");
    for(int i = 0; i < 5; i++) {
        printf("%d ", *ptr); 
        ptr++; 
    }
    free(inicio); 
}