void media_vetor() {
    int n, i, soma = 0;
    printf("Tamanho do vetor: ");
    scanf("%d", &n);

    int *vetor = (int *) malloc(n * sizeof(int));

    for(i = 0; i < n; i++) {
        printf("Elemento %d: ", i);
        scanf("%d", &vetor[i]);
        soma += vetor[i];
    }
    printf("Media: %.2f\n", (float)soma / n);
    free(vetor);
}