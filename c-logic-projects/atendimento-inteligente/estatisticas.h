#ifndef ESTATISTICAS_H
#define ESTATISTICAS_H

#include "lista.h"
#include "fila.h"

/* =============================================
   TAD Estatísticas
   Analisa o estado do sistema e exibe
   relatórios consolidados.
   ============================================= */

void estatisticas_exibir(const Lista *historico, const Fila *fila);

int arquivo_salvar(const Lista *historico, const char *caminho);

int arquivo_carregar(const char *caminho,
                     Lista *historico,
                     Fila  *fila,
                     void  *arvore,  
                     void  *hash,     
                     int   *proximo_id);

#endif
