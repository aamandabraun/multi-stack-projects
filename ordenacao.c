#include "utils.h"

// ================= BUBBLE SORT =================
void bubbleSort(Aluno v[], int n) {
    resetarContadores();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (v[j].nota > v[j + 1].nota) {
                trocar(&v[j], &v[j + 1]);
            }
        }
    }
}

// ================= SELECTION SORT =================
void selectionSort(Aluno v[], int n) {
    resetarContadores();
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (v[j].nota < v[min].nota) {
                min = j;
            }
        }
        if (min != i) {
            trocar(&v[i], &v[min]);
        }
    }
}

// ================= INSERTION SORT =================]
void insertionSort(Aluno v[], int n) {
    resetarContadores();

    for(int i = 1; i < n; i++){
        Aluno chave = v[i];
        int j = i - 1;

        while(j >= 0){
            comparacoes++;  

            if (v[j].nota > chave.nota) {
                v[j + 1] = v[j]; 
                trocas++;        
                j--;
            } else {
                break; 
            }
        }
        
        v[j + 1] = chave;
        
        if (j + 1 != i) {
            trocas++;
        }
        }
    }
}