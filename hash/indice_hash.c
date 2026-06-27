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

#include "indice_hash.h"

int comparar(const void *a, const void *b){
    EntradaHash *ea = *(EntradaHash **)a;
    EntradaHash *eb = *(EntradaHash **)b;
    return(strcmp(ea->palavra, eb->palavra));
}

void construirIndiceHash(TabelaHash *h, Corpus *corpus){
    for(int i = 0; i < corpus->tamanho; i++){
        inserirHash(h, corpus->tokens[i].palavra, corpus->tokens[i].idDoc);
    }
}

void imprimirIndiceHash(TabelaHash *h){
    EntradaHash *entradas[5000];
    int n = 0;
    
    for(int i = 0; i < M; i++){
        EntradaHash *atual = h->tabela[i];
        while(atual != NULL){
            entradas[n] = atual;
            n++;
            atual = atual->prox;
        }
    }
    
    qsort(entradas, n, sizeof(EntradaHash *), comparar);

    for(int i = 0; i < n; i++){
        printf("%s\n", entradas[i]->palavra);
        imprimirLista(&entradas[i]->ocorrencias);
        printf("\n"); 
    }
}

void calcularNi(TabelaHash *h, int *ni, int qtdDocs) {
    // zera o array
    for (int i = 0; i < qtdDocs; i++)
        ni[i] = 0;

    // percorre todos os slots da tabela
    for (int i = 0; i < M; i++) {
        EntradaHash *atual = h->tabela[i];

        // percorre a lista encadeada de palavras no slot i
        while (atual != NULL) {
            Celula *cel = atual->ocorrencias.primeiro;
            /* percorre a lista de ocorrências da palavra: cada célula representa um documento onde ela aparece, 
            então essa palavra conta +1 termo distinto naquele documento*/
            while (cel != NULL) {
                ni[cel->idDoc]++;
                cel = cel->prox;
            }

            atual = atual->prox;
        }
    }
}