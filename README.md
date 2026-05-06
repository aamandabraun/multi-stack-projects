# 🏃 Corrida de Algoritmos - Benchmark de Ordenação

## 📝 Visão Geral

Este projeto realiza uma **comparação detalhada** entre três algoritmos clássicos de ordenação:
- **Bubble Sort**
- **Selection Sort**
- **Insertion Sort**

O objetivo é analisar o desempenho de cada algoritmo em diferentes cenários (aleatório, ordenado, inverso) e visualizar os resultados através de tabelas, gráficos ASCII e rankings.

---

## 📁 Estrutura do Código

```
corrida-algoritmos/
├── aluno.h              # Definição da estrutura de dados
├── utils.h              # Cabeçalho de funções utilitárias
├── utils.c              # Implementação de funções utilitárias
├── ordenacao.h          # Cabeçalho dos algoritmos de ordenação
├── ordenacao.c          # Implementação dos algoritmos
├── main.c               # Teste simples dos algoritmos
├── comparacao.c         # Benchmark completo com gráficos
└── README.md            # Este arquivo
```

### Arquivos Principais

**`aluno.h`** - Estrutura de dados
```c
typedef struct {
    int matricula;
    char nome[50];
    float nota;
} Aluno;
```

---

## 🔍 Componentes Principais

### 1️⃣ Bubble Sort

**O que é?** O algoritmo mais simples. Percorre o vetor repetidamente, comparando elementos adjacentes e trocando-os se estiverem na ordem errada. "Borbulha" o maior elemento até o final a cada passagem.

**Implementação:**
```c
void bubbleSort(Aluno v[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (v[j].nota > v[j + 1].nota) {
                trocar(&v[j], &v[j + 1]);
                trocas++;
            }
        }
    }
}
```

**Complexidade:**
- **Melhor caso:** O(n) - Vetor já ordenado
- **Caso médio:** O(n²)
- **Pior caso:** O(n²) - Vetor em ordem inversa
- **Espaço:** O(1) - In-place
- **Estável:** Sim ✓

---

### 2️⃣ Selection Sort

**O que é?** Divide o vetor em duas partes: ordenada (esquerda) e não ordenada (direita). A cada iteração, encontra o elemento mínimo na parte não ordenada e o coloca no final da parte ordenada.

**Implementação:**
```c
void selectionSort(Aluno v[], int n) {
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
            trocas++;
        }
    }
}
```

**Complexidade:**
- **Melhor caso:** O(n²)
- **Caso médio:** O(n²)
- **Pior caso:** O(n²)
- **Espaço:** O(1) - In-place
- **Estável:** Não ✗

---

### 3️⃣ Insertion Sort

**O que é?** Constrói o vetor ordenado um elemento por vez. Para cada elemento, encontra a posição correta na parte já ordenada e o insere lá, deslocando os outros elementos.

**Implementação:**
```c
void insertionSort(Aluno v[], int n) {
    for (int i = 1; i < n; i++) {
        Aluno chave = v[i];
        int j = i - 1;
        while (j >= 0) {
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
    }
}
```

**Complexidade:**
- **Melhor caso:** O(n) - Vetor já ordenado
- **Caso médio:** O(n²)
- **Pior caso:** O(n²) - Vetor em ordem inversa
- **Espaço:** O(1) - In-place
- **Estável:** Sim ✓

---

## 🧪 Explicação dos Testes

### Cenários Testados

1. **Aleatório** - Dados em ordem completamente aleatória
2. **Ordenado** - Dados já em ordem crescente
3. **Inverso** - Dados em ordem completamente decrescente (pior caso)

### Métricas Coletadas

- **Comparações:** Número de vezes que dois elementos são comparados
- **Trocas:** Número de vezes que elementos mudam de posição
- **Tempo:** Tempo de execução em milissegundos

---

## 📊 Exemplos de Execução

### Exemplo 1: Teste Simples (main.c)

Compilar e executar:
```bash
gcc -o main main.c ordenacao.c utils.c
./main
```

**Saída esperada (N = 100):**
```
Bubble (Aleatorio) -> Comp: 4950 | Trocas: 2485
Selection (Aleatorio) -> Comp: 4950 | Trocas: 87
Insertion (Aleatorio) -> Comp: 2512 | Trocas: 2512

Bubble (Ordenado) -> Comp: 4950 | Trocas: 0
Selection (Ordenado) -> Comp: 4950 | Trocas: 0
Insertion (Ordenado) -> Comp: 99 | Trocas: 0

Bubble (Inverso) -> Comp: 4950 | Trocas: 4950
Selection (Inverso) -> Comp: 4950 | Trocas: 99
Insertion (Inverso) -> Comp: 5050 | Trocas: 5050
```

### Exemplo 2: Benchmark Completo (comparacao.c)

Compilar e executar:
```bash
gcc -o comparacao comparacao.c
./comparacao
```

**Saída esperada - Tabela Comparativa (N=1000):**
```
  +=============+============+======+===============+===============+=============+
  | Algoritmo   | Cenario    |   N  | Comparacoes   | Trocas        | Tempo(ms)   |
  +=============+============+======+===============+===============+=============+
  | BubbleSort  | Aleatorio  | 1000 |        499500 |        251453 |     35.2500 |
  | BubbleSort  | Ordenado   | 1000 |        999    |             0 |      0.1200 |
  | BubbleSort  | Inverso    | 1000 |        499500 |        499500 |     42.3100 |
  +-------------+------------+------+---------------+---------------+-------------+
  | SelectSort  | Aleatorio  | 1000 |        499500 |           499 |      8.5430 |
  | SelectSort  | Ordenado   | 1000 |        499500 |             0 |      8.3210 |
  | SelectSort  | Inverso    | 1000 |        499500 |           999 |      9.1250 |
  +-------------+------------+------+---------------+---------------+-------------+
  | InsertSort  | Aleatorio  | 1000 |        247512 |        247512 |     18.6540 |
  | InsertSort  | Ordenado   | 1000 |           999 |             0 |      0.0854 |
  | InsertSort  | Inverso    | 1000 |        500500 |        500500 |     42.1230 |
  +=============+============+======+===============+===============+=============+
```

---

## 📈 Gráficos e Visualizações

### Gráfico 1: Comparações por Algoritmo (N=1000)

```
  +------------------------------------------------------------------+
  |  COMPARACOES POR ALGORITMO E CENARIO                             |
  +------------------------------------------------------------------+
  | BubbleSort  Aleatorio |#########################################|     499500 |
  | BubbleSort  Ordenado  |##                                      |        999 |
  | BubbleSort  Inverso   |#########################################|     499500 |
  |                                                                  |
  | SelectSort  Aleatorio |#########################################|     499500 |
  | SelectSort  Ordenado  |#########################################|     499500 |
  | SelectSort  Inverso   |#########################################|     499500 |
  |                                                                  |
  | InsertSort  Aleatorio |===================                     |     247512 |
  | InsertSort  Ordenado  |##                                      |        999 |
  | InsertSort  Inverso   |**                                      |     500500 |
  +------------------------------------------------------------------+
  | Escala: cada '#','=','*' representa aprox. 13184 unidades        |
  +------------------------------------------------------------------+
```

### Gráfico 2: Trocas/Movimentações (N=1000)

```
  +------------------------------------------------------------------+
  |  TROCAS / MOVIMENTACOES POR ALGORITMO E CENARIO                  |
  +------------------------------------------------------------------+
  | BubbleSort  Aleatorio |#########################################|     251453 |
  | BubbleSort  Ordenado  |                                         |          0 |
  | BubbleSort  Inverso   |*****************************            |     499500 |
  |                                                                  |
  | SelectSort  Aleatorio |##                                      |        499 |
  | SelectSort  Ordenado  |                                         |          0 |
  | SelectSort  Inverso   |##                                      |        999 |
  |                                                                  |
  | InsertSort  Aleatorio |===================                     |     247512 |
  | InsertSort  Ordenado  |                                         |          0 |
  | InsertSort  Inverso   |*****************************            |     500500 |
  +------------------------------------------------------------------+
  | Escala: cada '#','=','*' representa aprox. 16684 unidades        |
  +------------------------------------------------------------------+
```

### 🏆 Ranking - Menor Número de Comparações

```
  +-------------------------------------------+
  |         RANKING - MENOR COMPARACOES        |
  +-------------------------------------------+
  | 1o  InsertSort / Ordenado   -> 999 comp
  | 2o  BubbleSort / Ordenado   -> 999 comp
  | 3o  SelectSort / Aleatorio  -> 499500 comp
  | 4o  SelectSort / Ordenado   -> 499500 comp
  | 5o  SelectSort / Inverso    -> 499500 comp
  | 6o  BubbleSort / Aleatorio  -> 499500 comp
  | 7o  BubbleSort / Inverso    -> 499500 comp
  | 8o  InsertSort / Aleatorio  -> 247512 comp
  | 9o  InsertSort / Inverso    -> 500500 comp
  +-------------------------------------------+
```

---

## 📊 Análise Teórica (Big-O)

```
  +----------------------------------------------------------------+
  |                  ANALISE TEORICA (Big-O)                       |
  +----------------------------------------------------------------+
  | Algoritmo      | Melhor Caso | Caso Medio  | Pior Caso | Estavel|
  +----------------+-------------+-------------+----------+--------+
  | Bubble Sort    |   O(n)      |   O(n^2)    |  O(n^2)  |  SIM   |
  | Selection Sort |   O(n^2)    |   O(n^2)    |  O(n^2)  |  NAO   |
  | Insertion Sort |   O(n)      |   O(n^2)    |  O(n^2)  |  SIM   |
  +----------------+-------------+-------------+----------+--------+
  | Espaço:        |   O(1) para todos (in-place)                  |
  +----------------------------------------------------------------+
```

---

## 🎯 Conclusões Principais

### 🥇 **Insertion Sort - O CAMPEÃO**
- **Melhor para:** Vetores já ordenados ou quase ordenados
- **Vantagem:** O(n) no melhor caso
- **Desvantagem:** O(n²) em casos aleatórios
- **Recomendação:** Use quando os dados tendem a estar parcialmente ordenados

### 🥈 **Selection Sort - O EQUILIBRADO**
- **Melhor para:** Quando o custo de escrita em memória é alto
- **Vantagem:** Número fixo de trocas O(n)
- **Desvantagem:** Sempre O(n²) comparações
- **Recomendação:** Use em sistemas com memória cara ou acesso lento

### 🥉 **Bubble Sort - O LENTO**
- **Melhor para:** Apenas fins educacionais
- **Vantagem:** Simples de entender e implementar
- **Desvantagem:** Pior desempenho geral, muitas trocas desnecessárias
- **Recomendação:** Evite em produção; use apenas para aprendizado

### 💡 **Dica Final**
Para dados aleatórios ou inversos, os três têm desempenho similar (O(n²)), mas **Insertion e Selection tendem a ser mais rápidos na prática** que Bubble Sort.

---

## 🔧 Como Compilar e Executar

### Teste Simples
```bash
gcc -o main main.c ordenacao.c utils.c
./main
```

### Benchmark Completo (Recomendado)
```bash
gcc -o comparacao comparacao.c
./comparacao
```

---

## 👥 Autores

Amanda  
Otavio  
Yara

---

## 📄 Licença

Este projeto é fornecido como material educacional.

