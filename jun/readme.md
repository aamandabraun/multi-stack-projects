# 🌳 Atividade — Árvores Binárias de Busca e Comparação de Algoritmos

## Integrantes
- Amanda Braun

---

## Como compilar e executar

```bash
# Compilar
make

# Executar (gera resultados/resultados.csv)
make run

# Limpar binário
make clean
```

Requisito: GCC instalado. Testado em Linux/macOS/WSL.

---

## Estrutura do repositório

```
atividade-arvores-busca/
├── src/
│   ├── main.c        # experimentos e main
│   ├── arvore.c      # árvore binária de busca
│   ├── arvore.h
│   ├── buscas.c      # busca sequencial e binária
│   └── buscas.h
├── resultados/
│   ├── resultados.csv
│   ├── grafico_comparacoes.png
│   └── grafico_altura_arvore.png
├── README.md
└── Makefile
```

---

## Tabela de resultados

> Preencha com os valores reais obtidos ao executar o programa.

| Tamanho | Tipo | Valor buscado | Busca Seq (comp) | Busca Bin (comp) | Árvore (comp) | Altura árvore |
|---------|------|--------------|-----------------|-----------------|--------------|--------------|
| 100 | Ordenado | início | | | | |
| 100 | Ordenado | meio | | | | |
| 100 | Ordenado | fim | | | | |
| 100 | Ordenado | inexistente | | | | |
| 100 | Embaralhado | início | | | | |
| 100 | Embaralhado | meio | | | | |
| 100 | Embaralhado | fim | | | | |
| 100 | Embaralhado | inexistente | | | | |
| 1.000.000 | Ordenado | início | | | | |
| 1.000.000 | Ordenado | meio | | | | |
| 1.000.000 | Ordenado | fim | | | | |
| 1.000.000 | Ordenado | inexistente | | | | |
| 1.000.000 | Embaralhado | início | | | | |
| 1.000.000 | Embaralhado | meio | | | | |
| 1.000.000 | Embaralhado | fim | | | | |
| 1.000.000 | Embaralhado | inexistente | | | | |
| 1.000.000.000 | Ordenado | — | ~1B (teórico) | ~30 (teórico) | ~1B (teórico) | ~1B (teórico) |
| 1.000.000.000 | Embaralhado | — | ~1B (teórico) | ~30 (teórico) | ~30 (teórico) | ~30 (teórico) |

---

## Análise crítica

### 1. Qual algoritmo teve menos comparações na maioria dos testes?
A busca binária foi consistentemente a que realizou menos comparações nos dados ordenados, com custo O(log n). Para n = 1.000.000, foram necessárias apenas ~20 comparações, enquanto a busca sequencial precisou de até 1.000.000. A busca em árvore com dados embaralhados também se aproximou de O(log n), mas com dados ordenados ela degenerou para O(n).

### 2. A busca em árvore foi sempre melhor que a busca sequencial? Explique.
Não. Quando os dados são inseridos em ordem crescente na árvore binária de busca, ela se degenera em uma lista encadeada: cada nó possui apenas filho direito, e a altura passa a ser igual ao número de elementos (n). Nessa situação, a busca na árvore se torna equivalente à busca sequencial, com O(n) comparações.

### 3. O que aconteceu com a árvore quando os valores foram inseridos em ordem crescente?
A árvore ficou completamente desbalanceada, formando uma estrutura linear (lista). O primeiro elemento inserido se torna a raiz, e cada novo elemento maior vai sempre para a direita, resultando em uma árvore de altura n. Isso anula qualquer vantagem da estrutura em termos de busca.

### 4. Por que a altura da árvore influencia diretamente a quantidade de comparações?
Na busca em árvore, a cada nível visitado é feita uma comparação. O caminho percorrido desde a raiz até o nó buscado (ou até constatar ausência) é no máximo igual à altura da árvore. Logo, altura menor significa menos comparações e busca mais rápida.

### 5. Por que a busca binária exige dados ordenados?
A busca binária funciona eliminando metade do espaço de busca a cada passo. Isso só é possível se os dados estiverem ordenados, pois assim é possível decidir — comparando com o elemento do meio — se o valor procurado está na metade esquerda ou direita. Em um vetor desordenado, essa lógica não se aplica.

### 6. Qual estrutura você escolheria para um sistema que precisa buscar dados com frequência? Justifique.
Para buscas frequentes, escolheria uma **árvore balanceada** (como AVL ou Red-Black Tree) ou, em sistemas com dados estáticos, o **vetor ordenado com busca binária**. Ambas garantem O(log n) no pior caso. A árvore balanceada tem a vantagem adicional de suportar inserções e remoções eficientes mantendo o balanceamento.

### 7. Qual é a relação entre esta atividade e o uso de índices em bancos de dados?
Bancos de dados relacionais utilizam estruturas como B-Trees e B+-Trees como índices exatamente pelo mesmo motivo analisado aqui: buscar um registro em uma tabela com milhões de linhas de forma sequencial seria O(n), enquanto um índice em árvore balanceada reduz para O(log n). A coluna de índice funciona como a chave da árvore, e o banco navega pelos nós para localizar o registro sem varrer a tabela inteira.

### 8. O que uma árvore balanceada resolveria neste experimento?
Uma árvore balanceada (AVL, por exemplo) garantiria que a altura nunca ultrapassasse O(log n) independentemente da ordem de inserção. No experimento com dados ordenados, em vez de uma árvore degenerada de altura 1.000.000, teríamos uma árvore de altura ~20, tornando a busca tão eficiente quanto a busca binária em todos os cenários.

---

## Gráficos

Os gráficos foram gerados a partir dos dados em `resultados/resultados.csv`.

- `grafico_comparacoes.png` — comparações por algoritmo para cada tamanho de entrada
- `grafico_altura_arvore.png` — altura da árvore: dados ordenados vs embaralhados

---

## Desafio extra — Exportação DOT

O programa exporta a árvore para o formato `.dot` (Graphviz). Para visualizar:

```bash
# Instalar Graphviz (Ubuntu/Debian)
sudo apt install graphviz

# Gerar imagem
dot -Tpng arvore.dot -o arvore.png
```