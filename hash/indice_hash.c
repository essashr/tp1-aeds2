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

// Função de comparação para ser usada no qsort para ordenar  as entradas da tabela em ordem alfabética
int comparar(const void *a, const void *b){
    // Realiza o cast do "a" para o tipo EntradaHash
    EntradaHash *ea = *(EntradaHash **)a;
    EntradaHash *eb = *(EntradaHash **)b;
    return(strcmp(ea->palavra, eb->palavra));
}


// Percorre por todo os tokens recebidos do Corpus e insere na tabela usando a função inserirHash()
void construirIndiceHash(TabelaHash *h, Corpus *corpus){
    for(int i = 0; i < corpus->tamanho; i++){
        inserirHash(h, corpus->tokens[i].palavra, corpus->tokens[i].idDoc);
    }
}

// Imprime o índice invertido em ordem alfabética 
void imprimirIndiceHash(TabelaHash *h){
    EntradaHash *entradas[M]; // Vetor auxiliar para juntar todos os ponteiros antes de ordenar
    int n = 0;
    
    // Percorre a tabela toda colocando no vetor entradas os ponteiros das entradas
    for(int i = 0; i < M; i++){
        EntradaHash *atual = h->tabela[i];
        while(atual != NULL){
            entradas[n] = atual;
            n++;
            atual = atual->prox;
        }
    }
    // Ordena o vetor em ordem alfabética usando o qsort com a função comparar 
    qsort(entradas, n, sizeof(EntradaHash *), comparar);
    // Percorre o vetor entradas imprimindo a palavra e a lista de ocorrências usando a função imprimirLista()
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