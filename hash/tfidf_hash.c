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

// Função de comparação para ser usada no qsort que ordena as relevâncias em ordem crescente 
int cmpRel(const void *a, const void *b){
    // Realiza o cast para o tipo ResultadosRel
    ResultadosRel *ea = (ResultadosRel*)a;
    ResultadosRel *eb = (ResultadosRel*)b;
    
    if(eb->relevancia > ea->relevancia) return 1;
    if(eb->relevancia < ea->relevancia) return -1;
    return 0;
}

// Calcula e acumula o peso TF-IDF de um termo de busca para cada documento em que ele existe
 void pesosTermo(char* palavra, TabelaHash *h, int n, double soma[]){
    // Busca o termo no indíce usand a buscarHash(), caso não existe não faz nada
    EntradaHash *entrada = buscarHash(h, palavra);
    if(entrada == NULL) return;

    // Conta em dj quantos doc distintos contem o termo (conta o tamanho da lista de ocorrência) 
    int dj = 0;
    Celula * atual = entrada->ocorrencias.primeiro;

    while(atual != NULL){
        dj++;
        atual = atual->prox;
    }
    // Percorre a lista e calcula e acumula os pesos de cada doc
    atual = entrada->ocorrencias.primeiro;
    while(atual != NULL){
        double w = atual->qtde * (log2((double)n) / dj);
        soma[atual->idDoc] += w;
        atual = atual->prox;
    }
 }
// Calcula a relevância de todos os docs para uma busca com um ou mais termos no modelo TF-IDF
int tfidf(TabelaHash *h, char **palavra, int qtdPalavras, int n, int *ni, ResultadosRel *resultados){
    // Aloca e zera o *soma onde vai acumular os pesos de cada doc 
    double *soma = calloc(n, sizeof(double));

    // Acumula o peso de cada termo da busca em todos os docs relevantes
    for(int i = 0; i < qtdPalavras; i++){
        pesosTermo(palavra[i], h, n, soma);
    }

    int quantosrel = 0;
    // Coleta em quantosrel a quantidade de docs com relevância maior que zero 
    for(int i = 0; i < n; i++){
        if(soma[i] > 0){
            resultados[quantosrel].idDoc = i;
            // Fase final da formula TF-IDF em que divide o somatório pelo ni (números de termos distintos do documento i)
            resultados[quantosrel].relevancia = soma[i] / ni[i];
            quantosrel++;
        }
    }

    free(soma);
    // Ordena usando qsort com a função cmpRel em ordem crescente
    qsort(resultados, quantosrel, sizeof(ResultadosRel), cmpRel);

    // Retorna quantos documentos relevantes foram encontrados
    return quantosrel;
}

// Imprime o nome do arquivo, título da fábula e a relevância
void imprimirRel(ResultadosRel *resultados, int quantosrel, Corpus *corpus) {
    for (int i = 0; i < quantosrel; i++) {
        printf("%s - %s -- Relevância %.2f\n",
        corpus->nomes[resultados[i].idDoc],
        corpus->titulos[resultados[i].idDoc],
        resultados[i].relevancia);
    }
}