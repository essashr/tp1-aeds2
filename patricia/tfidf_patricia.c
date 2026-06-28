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

TipoArvore pesquisa(const char *palavra, TipoArvore arv, int *qtdBusca){
    (*qtdBusca)++;
    if (arv->nt == Externo){
        if (strcmp(palavra, arv->NO.NoFolha.Chave) == 0){
            return arv;
        }else{
            return NULL;
        }
    }
     (*qtdBusca)++;
    if (palavra[arv->NO.NoInterno.Index] <= arv->NO.NoInterno.indexCaracter){
        return pesquisa(palavra, arv->NO.NoInterno.Esq, qtdBusca);
    }else{
        return pesquisa(palavra, arv->NO.NoInterno.Dir, qtdBusca);
    }
}

void calcular_peso(TipoArvore arv, char *palavra, int n, double soma[], int *qtdBusca){
    TipoArvore noDaPalavra = pesquisa(palavra, arv, qtdBusca);

    if (noDaPalavra == NULL) return;

    int dj = 0;

    Celula* atual = noDaPalavra->NO.NoFolha.Lista.primeiro;

    while (atual != NULL)
    {
       dj++;
       atual = atual->prox;
    }
    
    atual = noDaPalavra->NO.NoFolha.Lista.primeiro;

    while (atual != NULL)
    {
        double w = atual->qtde * (log2((double)n) / dj);
        soma[atual->idDoc] += w;
        atual = atual->prox;
    }
    


}

int tfidf_patricia(TipoArvore arv, char **palavras, int qtdPalavras, int n, int *ni, prioridade *resultados, int *qtdBusca){

    double *soma = calloc(n, sizeof(double));
    int i;

    for (i=0; i< qtdPalavras; i++){
        calcular_peso(arv, palavras[i], n, soma, qtdBusca);
    }

    int quantidadeRel = 0;

    for (i=0; i < n; i++){
        if (soma[i] > 0){
            resultados[quantidadeRel].iddoc = i;
            resultados[quantidadeRel].valor = soma[i] / ni[i];
            quantidadeRel++;
        }
    }

    free(soma);

    qsort(resultados, quantidadeRel, sizeof(prioridade), compara_prioridade);

    return quantidadeRel;

}

void imprimirRel_patricia(prioridade *resultados, int quantosrel, Corpus *corpus){
    for(int i=0; i< quantosrel; i++){
        printf("%s - %s -- Relevância %.2f\n",
        corpus->nomes[resultados[i].iddoc],
        corpus->titulos[resultados[i].iddoc],
        resultados[i].valor);
    }
}

