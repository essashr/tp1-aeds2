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

#include "tfidf_hash.h"

int cmpRel(const void *a, const void *b){
    ResultadosRel *ea = (ResultadosRel*)a;
    ResultadosRel *eb = (ResultadosRel*)b;

    if(eb->relevancia > ea->relevancia) return 1;
    if(eb->relevancia < ea->relevancia) return -1;
    return 0;
}

 void pesosTermo(char* palavra, TabelaHash *h, int n, double soma[]){
    EntradaHash *entrada = buscarHash(h, palavra);
    if(entrada == NULL) return;

    int dj = 0;
    Celula * atual = entrada->ocorrencias.primeiro;

    while(atual != NULL){
        dj++;
        atual = atual->prox;
    }
    
    atual = entrada->ocorrencias.primeiro;
    while(atual != NULL){
        double w = atual->qtde * (log2((double)n) / dj);
        soma[atual->idDoc] += w;
        atual = atual->prox;
    }
 }

int tfidf(TabelaHash *h, char **palavra, int qtdPalavras, int n, int *ni, ResultadosRel *resultados){

    double *soma = calloc(n, sizeof(double));

    for(int i = 0; i < qtdPalavras; i++){
        pesosTermo(palavra[i], h, n, soma);
    }

    int quantosrel = 0;

    for(int i = 0; i < n; i++){
        if(soma[i] > 0){
            resultados[quantosrel].idDoc = i;
            resultados[quantosrel].relevancia = soma[i] / ni[i];
            quantosrel++;
        }
    }

    free(soma);

    qsort(resultados, quantosrel, sizeof(ResultadosRel), cmpRel);

    return quantosrel;
}

void imprimirRel(ResultadosRel *resultados, int quantosrel, Corpus *corpus) {
    for (int i = 0; i < quantosrel; i++) {
        printf("%s - %s -- Relevância %.2f\n",
        corpus->nomes[resultados[i].idDoc],
        corpus->titulos[resultados[i].idDoc],
        resultados[i].relevancia);
    }
}