#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    int   matricula;
    char  nome[50];
    float nota;
} Aluno;

long long comparacoes = 0;
long long trocas      = 0;

void resetarContadores() {
    comparacoes = 0;
    trocas      = 0;
}

void trocar(Aluno *a, Aluno *b) {
    Aluno tmp = *a; *a = *b; *b = tmp;
}

void copiarVetor(Aluno dest[], Aluno src[], int n) {
    memcpy(dest, src, n * sizeof(Aluno));
}

void gerarAleatorio(Aluno v[], int n) {
    for (int i = 0; i < n; i++) {
        v[i].matricula = i + 1;
        sprintf(v[i].nome, "Aluno%d", i + 1);
        v[i].nota = (rand() % 101) / 10.0f;
    }
}

void gerarOrdenado(Aluno v[], int n) {
    for (int i = 0; i < n; i++) {
        v[i].matricula = i + 1;
        sprintf(v[i].nome, "Aluno%d", i + 1);
        v[i].nota = (float)i / n * 10.0f;
    }
}

void gerarInverso(Aluno v[], int n) {
    for (int i = 0; i < n; i++) {
        v[i].matricula = i + 1;
        sprintf(v[i].nome, "Aluno%d", i + 1);
        v[i].nota = 10.0f - (float)i / n * 10.0f;
    }
}

/* ===================== ALGORITMOS ===================== */
void bubbleSort(Aluno v[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (v[j].nota > v[j+1].nota) {
                trocar(&v[j], &v[j+1]);
                trocas++;
            }
        }
}

void selectionSort(Aluno v[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (v[j].nota < v[min].nota) min = j;
        }
        if (min != i) { trocar(&v[i], &v[min]); trocas++; }
    }
}

void insertionSort(Aluno v[], int n) {
    for (int i = 1; i < n; i++) {
        Aluno chave = v[i];
        int j = i - 1;
        while (j >= 0) {
            comparacoes++;
            if (v[j].nota > chave.nota) {
                v[j+1] = v[j]; trocas++; j--;
            } else break;
        }
        v[j+1] = chave;
    }
}

/* ===================== RESULTADO ===================== */
typedef struct {
    char   algoritmo[20];
    char   cenario[15];
    int    n;
    long long comp;
    long long trocas;
    double tempo_ms;
} Resultado;

/* ===================== GRAFICO ASCII ===================== */
#define BAR_MAX 50

void barraASCII(long long valor, long long maximo, char c) {
    int tamanho = (maximo > 0) ? (int)((double)valor / maximo * BAR_MAX) : 0;
    for (int i = 0; i < tamanho; i++) putchar(c);
    for (int i = tamanho; i < BAR_MAX; i++) putchar(' ');
}

void imprimirGrafico(Resultado res[], int total, const char *titulo, int usarTrocas) {
    long long maximo = 0;
    for (int i = 0; i < total; i++) {
        long long v = usarTrocas ? res[i].trocas : res[i].comp;
        if (v > maximo) maximo = v;
    }

    printf("\n");
    printf("  +------------------------------------------------------------------+\n");
    printf("  |  %-64s|\n", titulo);
    printf("  +------------------------------------------------------------------+\n");

    char *cores[] = {"#", "=", "*"}; 
    int idx = 0;
    char ultimo_algo[20] = "";

    for (int i = 0; i < total; i++) {
        long long v = usarTrocas ? res[i].trocas : res[i].comp;

        if (strcmp(res[i].algoritmo, ultimo_algo) != 0) {
            if (i > 0) printf("  |                                                                  |\n");
            strcpy(ultimo_algo, res[i].algoritmo);
            idx++;
        }

        char rotulo[40];
        sprintf(rotulo, "%-10s %-10s", res[i].algoritmo, res[i].cenario);
        printf("  | %-22s |", rotulo);
        barraASCII(v, maximo, cores[idx % 3][0]);
        printf("| %8lld |\n", v);
    }
    printf("  +------------------------------------------------------------------+\n");
    printf("  | Escala: cada '#','=','*' representa aprox. %lld unidades%*s|\n",
           maximo / BAR_MAX, (int)(20 - (maximo > 9999 ? 5 : maximo > 999 ? 4 : 3)), " ");
    printf("  +------------------------------------------------------------------+\n");
}

/* ===================== TABELA COMPARATIVA ===================== */
void imprimirTabelaComparativa(Resultado res[], int total) {
    printf("\n");
    printf("  +=============+============+======+===============+===============+=============+\n");
    printf("  | %-11s | %-10s | %-4s | %-13s | %-13s | %-11s |\n",
           "Algoritmo", "Cenario", "N", "Comparacoes", "Trocas", "Tempo(ms)");
    printf("  +=============+============+======+===============+===============+=============+\n");

    char ultimo[20] = "";
    for (int i = 0; i < total; i++) {
        if (i > 0 && strcmp(res[i].algoritmo, ultimo) != 0)
            printf("  +-------------+------------+------+---------------+---------------+-------------+\n");
        strcpy(ultimo, res[i].algoritmo);

        printf("  | %-11s | %-10s | %4d | %13lld | %13lld | %11.4f |\n",
               res[i].algoritmo,
               res[i].cenario,
               res[i].n,
               res[i].comp,
               res[i].trocas,
               res[i].tempo_ms);
    }
    printf("  +=============+============+======+===============+===============+=============+\n");
}

/* ===================== RANKING ===================== */
void imprimirRanking(Resultado res[], int total) {
    printf("\n");
    printf("  +-------------------------------------------+\n");
    printf("  |         RANKING - MENOR COMPARACOES        |\n");
    printf("  +-------------------------------------------+\n");

    Resultado copia[100];
    int n = total;
    memcpy(copia, res, total * sizeof(Resultado));
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (copia[j].comp > copia[j+1].comp) {
                Resultado tmp = copia[j]; copia[j] = copia[j+1]; copia[j+1] = tmp;
            }

    char *medalha[] = {"1o", "2o", "3o", "4o", "5o", "6o", "7o", "8o", "9o"};
    for (int i = 0; i < n; i++)
        printf("  | %s  %-11s / %-10s -> %lld comp\n",
               medalha[i], copia[i].algoritmo, copia[i].cenario, copia[i].comp);

    printf("  +-------------------------------------------+\n");
}

/* ===================== ANALISE ===================== */
void imprimirAnalise() {
    printf("\n");
    printf("  +================================================================+\n");
    printf("  |                  ANALISE TEORICA (Big-O)                       |\n");
    printf("  +================================================================+\n");
    printf("  | Algoritmo     | Melhor Caso | Caso Medio  | Pior Caso  | Estavel|\n");
    printf("  +---------------+-------------+-------------+------------+--------+\n");
    printf("  | Bubble Sort   |   O(n)      |   O(n^2)    |   O(n^2)   |  SIM   |\n");
    printf("  | Selection Sort|   O(n^2)    |   O(n^2)    |   O(n^2)   |  NAO   |\n");
    printf("  | Insertion Sort|   O(n)      |   O(n^2)    |   O(n^2)   |  SIM   |\n");
    printf("  +---------------+-------------+-------------+------------+--------+\n");
    printf("  | Espaco:       |   O(1) para todos (in-place)                   |\n");
    printf("  +================================================================+\n");

    printf("\n");
    printf("  +================================================================+\n");
    printf("  |                     CONCLUSOES                                 |\n");
    printf("  +================================================================+\n");
    printf("  | >> INSERTION SORT: melhor para vetores ja ordenados ou         |\n");
    printf("  |    quase ordenados (O(n) no melhor caso).                      |\n");
    printf("  |                                                                |\n");
    printf("  | >> SELECTION SORT: numero fixo de trocas O(n), util quando     |\n");
    printf("  |    escrita em memoria e cara.                                  |\n");
    printf("  |                                                                |\n");
    printf("  | >> BUBBLE SORT: pior desempenho geral; unico ponto positivo    |\n");
    printf("  |    e a deteccao de vetor ja ordenado (com flag).               |\n");
    printf("  |                                                                |\n");
    printf("  | >> Para dados aleatorios ou inversos, os tres tem desempenho   |\n");
    printf("  |    similar (O(n^2)), mas Insertion e Selection tendem a ser    |\n");
    printf("  |    mais rapidos na pratica que Bubble.                         |\n");
    printf("  +================================================================+\n");
}

int main() {
    srand((unsigned)time(NULL));

    int tamanhos[] = {100, 500, 1000};
    int num_tamanhos = 3;

    char *cenarios[]  = {"Aleatorio", "Ordenado", "Inverso"};
    int   num_cenarios = 3;

    Resultado resultados[100];
    int       total = 0;

    printf("\n");
    printf("  ################################################################\n");
    printf("  ##      CORRIDA DE ALGORITMOS - Benchmark de Ordenacao        ##\n");
    printf("  ##      Bubble Sort x Selection Sort x Insertion Sort         ##\n");
    printf("  ##      Amanda, Otavio e Yara                                  ##\n");
    printf("  ################################################################\n");

    for (int t = 0; t < num_tamanhos; t++) {
        int n = tamanhos[t];
        Aluno *base   = malloc(n * sizeof(Aluno));
        Aluno *vetor  = malloc(n * sizeof(Aluno));

        printf("\n  [Testando N = %d ...]\n", n);

        for (int c = 0; c < num_cenarios; c++) {
            if (c == 0) gerarAleatorio(base, n);
            else if (c == 1) gerarOrdenado(base, n);
            else             gerarInverso(base, n);

            /* --- Bubble Sort --- */
            copiarVetor(vetor, base, n);
            resetarContadores();
            clock_t t1 = clock();
            bubbleSort(vetor, n);
            clock_t t2 = clock();
            resultados[total].n = n;
            strcpy(resultados[total].algoritmo, "BubbleSort");
            strcpy(resultados[total].cenario, cenarios[c]);
            resultados[total].comp     = comparacoes;
            resultados[total].trocas   = trocas;
            resultados[total].tempo_ms = (double)(t2 - t1) / CLOCKS_PER_SEC * 1000.0;
            total++;

            /* --- Selection Sort --- */
            copiarVetor(vetor, base, n);
            resetarContadores();
            t1 = clock();
            selectionSort(vetor, n);
            t2 = clock();
            resultados[total].n = n;
            strcpy(resultados[total].algoritmo, "SelectSort");
            strcpy(resultados[total].cenario, cenarios[c]);
            resultados[total].comp     = comparacoes;
            resultados[total].trocas   = trocas;
            resultados[total].tempo_ms = (double)(t2 - t1) / CLOCKS_PER_SEC * 1000.0;
            total++;

            /* --- Insertion Sort --- */
            copiarVetor(vetor, base, n);
            resetarContadores();
            t1 = clock();
            insertionSort(vetor, n);
            t2 = clock();
            resultados[total].n = n;
            strcpy(resultados[total].algoritmo, "InsertSort");
            strcpy(resultados[total].cenario, cenarios[c]);
            resultados[total].comp     = comparacoes;
            resultados[total].trocas   = trocas;
            resultados[total].tempo_ms = (double)(t2 - t1) / CLOCKS_PER_SEC * 1000.0;
            total++;
        }

        free(base);
        free(vetor);
    }

    Resultado sub[30];
    int nsub = 0;
    for (int i = 0; i < total; i++)
        if (resultados[i].n == 1000) sub[nsub++] = resultados[i];

    printf("\n\n");
    printf("  ================================================================\n");
    printf("  =               TABELA COMPARATIVA COMPLETA                    =\n");
    printf("  ================================================================\n");
    imprimirTabelaComparativa(resultados, total);

    printf("\n\n");
    printf("  ================================================================\n");
    printf("  =         GRAFICOS DE BARRAS ASCII  (N = 1000)                 =\n");
    printf("  ================================================================\n");
    imprimirGrafico(sub, nsub, "COMPARACOES POR ALGORITMO E CENARIO", 0);
    imprimirGrafico(sub, nsub, "TROCAS / MOVIMENTACOES POR ALGORITMO E CENARIO", 1);

    imprimirRanking(sub, nsub);

    imprimirAnalise();

    printf("\n  Benchmark concluido.\n\n");
    return 0;
}