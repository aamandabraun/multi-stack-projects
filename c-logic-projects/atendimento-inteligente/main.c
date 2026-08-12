#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "atendimento.h"
#include "fila.h"
#include "lista.h"
#include "arvore.h"
#include "hash.h"
#include "ordenacao.h"
#include "estatisticas.h"

/* =============================================
   main.c — Ponto de entrada e menu do sistema
   ============================================= */

#define ARQUIVO_CSV "atendimentos.csv"

/* --- Estado global do sistema --- */
static Fila   fila;
static Lista  historico;
static Arvore arvore;
static Hash   hash;
static int    proximo_id = 1;

/* --- Utilitários de entrada --- */

static void limpar_buffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

static void ler_string(const char *prompt, char *dest, int max)
{
    printf("%s", prompt);
    if (fgets(dest, max, stdin)) {
        dest[strcspn(dest, "\n")] = '\0';
    }
}

static int ler_int(const char *prompt, int min, int max_val)
{
    int valor;
    while (1) {
        printf("%s", prompt);
        if (scanf("%d", &valor) == 1) {
            limpar_buffer();
            if (valor >= min && valor <= max_val)
                return valor;
        } else {
            limpar_buffer();
        }
        printf("  Valor invalido. Digite entre %d e %d.\n", min, max_val);
    }
}

/* --- Ações do menu --- */

static void acao_cadastrar(void)
{
    char cliente[50], categoria[30];
    printf("\n  -- Cadastrar Atendimento --\n");
    ler_string("  Nome do cliente  : ", cliente,   sizeof(cliente));
    ler_string("  Categoria        : ", categoria, sizeof(categoria));
    int prio  = ler_int("  Prioridade (1=baixa 2=media 3=alta): ", 1, 3);
    int tempo = ler_int("  Tempo estimado (min)               : ", 1, 9999);

    Atendimento a = atendimento_criar(proximo_id++, cliente, categoria, prio, tempo);
    lista_inserir(&historico, a);
    fila_enfileirar(&fila, a);
    arvore_inserir(&arvore, a);
    hash_inserir(&hash, a);

    printf("  Atendimento #%d cadastrado com sucesso!\n\n", a.id);
}

static void acao_atender_proximo(void)
{
    printf("\n  -- Atender Proximo da Fila --\n");
    Atendimento a;
    if (!fila_desenfileirar(&fila, &a)) return;

    strncpy(a.status, "atendido", sizeof(a.status) - 1);
    lista_alterar_status(&historico, a.id, "atendido");
    arvore_atualizar_status(&arvore,  a.id, "atendido");
    hash_atualizar_status(&hash,      a.id, "atendido");

    printf("  Atendimento realizado:\n");
    atendimento_exibir(&a);
}

static void acao_cancelar(void)
{
    printf("\n  -- Cancelar Atendimento --\n");
    int id = ler_int("  ID do atendimento: ", 1, 999999);

    int na_fila = fila_remover_por_id(&fila, id);
    int no_hist = lista_alterar_status(&historico, id, "cancelado");
    arvore_atualizar_status(&arvore, id, "cancelado");
    hash_atualizar_status(&hash,     id, "cancelado");

    if (no_hist)
        printf("  Atendimento #%d cancelado.%s\n\n",
               id, na_fila ? " (removido da fila)" : "");
    else
        printf("  ID #%d nao encontrado.\n\n", id);
}

static void acao_listar_fila(void)
{
    printf("\n  ===== FILA DE ESPERA (%d) =====\n", fila.tamanho);
    fila_listar(&fila);
    printf("\n");
}

static void acao_listar_historico(void)
{
    printf("\n  ===== HISTORICO (%d) =====\n", historico.tamanho);
    lista_listar(&historico);
    printf("\n");
}

static void acao_buscar_cliente(void)
{
    char nome[50];
    printf("\n  -- Busca por Cliente --\n");
    ler_string("  Nome (parcial): ", nome, sizeof(nome));
    int n = lista_buscar_por_cliente(&historico, nome);
    printf("  %d resultado(s) encontrado(s).\n\n", n);
}

static void acao_buscar_prioridade(void)
{
    printf("\n  -- Busca por Prioridade --\n");
    int p = ler_int("  Prioridade (1=baixa 2=media 3=alta): ", 1, 3);
    int n = lista_buscar_por_prioridade(&historico, p);
    printf("  %d resultado(s) encontrado(s).\n\n", n);
}

static void acao_buscar_id_arvore(void)
{
    printf("\n  -- Busca por ID (Arvore BST) --\n");
    int id = ler_int("  ID: ", 1, 999999);
    Atendimento *a = arvore_buscar(&arvore, id);
    if (a) {
        printf("  Encontrado:\n");
        atendimento_exibir(a);
    } else {
        printf("  ID #%d nao encontrado na arvore.\n\n", id);
    }
}

static void acao_buscar_categoria_hash(void)
{
    char cat[30];
    printf("\n  -- Busca por Categoria (Hash) --\n");
    ler_string("  Categoria: ", cat, sizeof(cat));
    int n = hash_buscar_por_categoria(&hash, cat);
    printf("  %d resultado(s) encontrado(s).\n\n", n);
}

static void acao_ordenar_prioridade(void)
{
    printf("\n  Ordenando historico por prioridade (alta -> baixa)...\n");
    ordenar_por_prioridade(&historico);
    lista_listar(&historico);
}

static void acao_ordenar_tempo(void)
{
    printf("\n  Ordenando historico por tempo estimado (menor -> maior)...\n");
    ordenar_por_tempo_estimado(&historico);
    lista_listar(&historico);
}

static void acao_ordenar_multiplo(void)
{
    printf("\n  Ordenando por prioridade (alta) e tempo (menor)...\n");
    ordenar_por_prioridade_e_tempo(&historico);
    lista_listar(&historico);
}

static void acao_estatisticas(void)
{
    estatisticas_exibir(&historico, &fila);
    hash_categoria_mais_atendimentos(&hash);
}

static void acao_salvar(void)
{
    printf("\n  -- Salvar em arquivo --\n");
    arquivo_salvar(&historico, ARQUIVO_CSV);
    printf("\n");
}

static void acao_gerar_testes(void)
{
    printf("\n  -- Gerar atendimentos de teste --\n");
    const char *clientes[]    = {"Ana Lima","Bruno Costa","Carla Souza",
                                  "Diego Nunes","Elena Ramos","Fabio Alves",
                                  "Gabi Torres","Hugo Faria"};
    const char *categorias[]  = {"Hardware","Software","Rede","Impressora","Email"};
    int n = ler_int("  Quantos atendimentos gerar? (1-20): ", 1, 20);

    srand((unsigned)time(NULL));
    int i;
    for (i = 0; i < n; i++) {
        const char *cli  = clientes[rand()  % 8];
        const char *cat  = categorias[rand() % 5];
        int prio  = (rand() % 3) + 1;
        int tempo = (rand() % 60) + 5;
        Atendimento a = atendimento_criar(proximo_id++, cli, cat, prio, tempo);
        lista_inserir(&historico, a);
        fila_enfileirar(&fila, a);
        arvore_inserir(&arvore, a);
        hash_inserir(&hash, a);
    }
    printf("  %d atendimento(s) gerado(s).\n\n", n);
}

/* --- Menu --- */

static void exibir_menu(void)
{
    printf("\n===== SISTEMA DE ATENDIMENTOS TECNICOS =====\n");
    printf("  Fila: %d | Historico: %d\n", fila.tamanho, historico.tamanho);
    printf("--------------------------------------------\n");
    printf("  1  - Cadastrar atendimento\n");
    printf("  2  - Atender proximo da fila\n");
    printf("  3  - Cancelar atendimento\n");
    printf("  4  - Listar fila de espera\n");
    printf("  5  - Listar historico\n");
    printf("  6  - Buscar por nome do cliente\n");
    printf("  7  - Buscar por prioridade\n");
    printf("  8  - Buscar por ID (arvore BST)\n");
    printf("  9  - Buscar por categoria (hash)\n");
    printf("  10 - Ordenar historico por prioridade\n");
    printf("  11 - Ordenar historico por tempo estimado\n");
    printf("  12 - Ordenar por prioridade + tempo\n");
    printf("  13 - Exibir estatisticas\n");
    printf("  14 - Salvar historico em arquivo\n");
    printf("  15 - Gerar atendimentos de teste\n");
    printf("  0  - Sair\n");
    printf("--------------------------------------------\n");
    printf("  Opcao: ");
}

int main(void)
{
    /* Inicializa estruturas */
    fila_inicializar(&fila);
    lista_inicializar(&historico);
    arvore_inicializar(&arvore);
    hash_inicializar(&hash);

    /* Tenta carregar dados anteriores */
    arquivo_carregar(ARQUIVO_CSV, &historico, &fila,
                     &arvore, &hash, &proximo_id);

    int opcao;
    do {
        exibir_menu();
        if (scanf("%d", &opcao) != 1) { limpar_buffer(); opcao = -1; }
        else limpar_buffer();

        switch (opcao) {
            case  1: acao_cadastrar();           break;
            case  2: acao_atender_proximo();     break;
            case  3: acao_cancelar();            break;
            case  4: acao_listar_fila();         break;
            case  5: acao_listar_historico();    break;
            case  6: acao_buscar_cliente();      break;
            case  7: acao_buscar_prioridade();   break;
            case  8: acao_buscar_id_arvore();    break;
            case  9: acao_buscar_categoria_hash();break;
            case 10: acao_ordenar_prioridade();  break;
            case 11: acao_ordenar_tempo();       break;
            case 12: acao_ordenar_multiplo();    break;
            case 13: acao_estatisticas();        break;
            case 14: acao_salvar();              break;
            case 15: acao_gerar_testes();        break;
            case  0: printf("\n  Salvando e encerrando...\n"); break;
            default: printf("  Opcao invalida.\n");
        }
    } while (opcao != 0);

    /* Salva automaticamente ao sair */
    arquivo_salvar(&historico, ARQUIVO_CSV);

    /* Libera memória */
    fila_destruir(&fila);
    lista_destruir(&historico);
    arvore_destruir(&arvore);
    hash_destruir(&hash);

    printf("  Memoria liberada. Ate logo!\n\n");
    return 0;
}
