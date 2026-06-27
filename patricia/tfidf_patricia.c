/*
 * CCF212 - Algoritmos e Estruturas de Dados II - 2026/1
 * Trabalho Pratico I - Grupo TP1-AEDS2
 *
 * Integrantes:
 *   Arthur Emanoel Alecrim Correia  - 6582
 *   Ryan Italo de Andrade Ananias   - 6588
 *   Thomaz Augusto Araujo Silva     - 6577
 *   Alejandro Mateus Escobar Cavalcante - 6598
 */

#include "tfidf_patricia.h"

int compara_prioridade(const void *a, const void *b) {
    prioridade *ea = (prioridade *)a;
    prioridade *eb = (prioridade *)b;

    if (eb->valor > ea->valor) return 1;
    if (eb->valor < ea->valor) return -1;
    return 0;
}

int consulta_dj(char *palavra, TipoArvore arv){
    TipoArvore no = pesquisa(palavra, arv);
    if (no == NULL)
        return 0;
    int dj = 0;
    Celula *p = no->NO.NoFolha.Lista.primeiro;
    while (p != NULL){
        dj++;
        p = p->prox;
    }
    return dj;
}

void calcular_prioridade(TipoArvore arv, int v[], int n, char *palavra, prioridade pri[]){
    int dj = consulta_dj(palavra, arv);
    if (dj == 0)
        return;

    double fator = log2((double)n / dj);

    for (int i = 0; i < n; i++){

        pri[i].valor += v[i] * fator;
        pri[i].iddoc = i;
    }
    qsort(pri, n, sizeof(prioridade), compara_prioridade);

    impressão(pri, n);
}

void impressão_relevancia(prioridade pri[], int n){
    for (int i = 0; i < n; i++){
        if (pri != 0){
            printf("id: %dRelevancia: %.4f\n", pri[i].iddoc, pri[i].valor);
        }
    }
}

