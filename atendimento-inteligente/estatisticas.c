#include <stdio.h>
#include <string.h>
#include "estatisticas.h"
#include "arvore.h"
#include "hash.h"

/* =============================================
   Implementação de Estatísticas e Persistência
   ============================================= */

void estatisticas_exibir(const Lista *historico, const Fila *fila)
{
    int total      = 0;
    int atendidos  = 0;
    int cancelados = 0;
    int abertos    = 0;
    int p_baixa    = 0;
    int p_media    = 0;
    int p_alta     = 0;
    int tempo_total = 0;

    NoLista *atual = historico->cabeca;
    while (atual) {
        total++;
        tempo_total += atual->dado.tempo_estimado;

        if (strcmp(atual->dado.status, "atendido")  == 0) atendidos++;
        else if (strcmp(atual->dado.status, "cancelado") == 0) cancelados++;
        else abertos++;

        switch (atual->dado.prioridade) {
            case 1: p_baixa++; break;
            case 2: p_media++; break;
            case 3: p_alta++;  break;
        }
        atual = atual->proximo;
    }

    printf("\n  ====== ESTATISTICAS DO SISTEMA ======\n");
    printf("  Total de atendimentos  : %d\n",   total);
    printf("  Atendidos              : %d\n",   atendidos);
    printf("  Cancelados             : %d\n",   cancelados);
    printf("  Em aberto (historico)  : %d\n",   abertos);
    printf("  Na fila de espera      : %d\n",   fila->tamanho);
    printf("  ---- Por prioridade ----\n");
    printf("  Alta  (3)              : %d\n",   p_alta);
    printf("  Media (2)              : %d\n",   p_media);
    printf("  Baixa (1)              : %d\n",   p_baixa);
    printf("  ---- Tempo ----\n");
    printf("  Tempo total estimado   : %d min\n", tempo_total);
    if (total > 0)
        printf("  Tempo medio estimado   : %.1f min\n", (float)tempo_total / total);
    printf("  =====================================\n\n");
}

int arquivo_salvar(const Lista *historico, const char *caminho)
{
    FILE *f = fopen(caminho, "w");
    if (!f) {
        fprintf(stderr, "Erro: nao foi possivel abrir '%s' para escrita.\n", caminho);
        return 0;
    }
    fprintf(f, "id,cliente,categoria,prioridade,tempo_estimado,status\n");

    NoLista *atual = historico->cabeca;
    while (atual) {
        const Atendimento *a = &atual->dado;
        fprintf(f, "%d,%s,%s,%d,%d,%s\n",
                a->id, a->cliente, a->categoria,
                a->prioridade, a->tempo_estimado, a->status);
        atual = atual->proximo;
    }
    fclose(f);
    printf("  Historico salvo em '%s'.\n", caminho);
    return 1;
}

int arquivo_carregar(const char *caminho,
                     Lista *historico,
                     Fila  *fila,
                     void  *arv,
                     void  *hsh,
                     int   *proximo_id)
{
    FILE *f = fopen(caminho, "r");
    if (!f) {
        printf("  Arquivo '%s' nao encontrado. Iniciando vazio.\n", caminho);
        return 0;
    }

    char linha[256];
    if (!fgets(linha, sizeof(linha), f)) { fclose(f); return 0; }

    Arvore *arvore = (Arvore *)arv;
    Hash   *hash   = (Hash   *)hsh;
    int carregados = 0;

    while (fgets(linha, sizeof(linha), f)) {
        Atendimento a;
        char status[20];
        if (sscanf(linha, "%d,%49[^,],%29[^,],%d,%d,%19[^\n]",
                   &a.id, a.cliente, a.categoria,
                   &a.prioridade, &a.tempo_estimado, status) == 6) {
            strncpy(a.status, status, sizeof(a.status) - 1);
            a.status[sizeof(a.status) - 1] = '\0';

            lista_inserir(historico, a);
            arvore_inserir(arvore, a);
            hash_inserir(hash, a);

            if (strcmp(a.status, "aberto") == 0)
                fila_enfileirar(fila, a);

            if (a.id >= *proximo_id)
                *proximo_id = a.id + 1;

            carregados++;
        }
    }
    fclose(f);
    printf("  %d atendimento(s) carregado(s) de '%s'.\n", carregados, caminho);
    return carregados;
}
