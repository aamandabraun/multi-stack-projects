int** alocar_matriz(int m, int n) {
    int **matriz = (int **) malloc(m * sizeof(int *)); 
    for (int i = 0; i < m; i++) {
        matriz[i] = (int *) malloc(n * sizeof(int)); 
    }
    return matriz;
}

void liberar_matriz(int **matriz, int m) {
    for (int i = 0; i < m; i++) {
        free(matriz[i]); 
    }
    free(matriz); 
}