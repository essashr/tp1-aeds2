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
// comparar dois elementos e dizer quem deve vir primeiro usada para o qsort.
int compara_prioridade(const void *a, const void *b) {
    prioridade *ea = (prioridade *)a;
    prioridade *eb = (prioridade *)b;

    if (eb->valor > ea->valor) return 1;
    if (eb->valor < ea->valor) return -1;
    return 0;
}
//faz a procura da palavra e quantas nos foram visitados 
TipoArvore pesquisa(const char *palavra, TipoArvore arv, int *qtdBusca){
    (*qtdBusca)++;
    //verifica se o no é externo para saber se deve retornar aquela folha
    if (arv->nt == Externo){
        if (strcmp(palavra, arv->NO.NoFolha.Chave) == 0){
            return arv;
        }else{
            return NULL;
        }
    }
    //incrementa para saber a quantidade de visitas
     (*qtdBusca)++;
     //verifica se a letra que difere nos no interno é maior ou menor e chama recursivamente para o lado certo 
    if (palavra[arv->NO.NoInterno.Index] <= arv->NO.NoInterno.indexCaracter){
        return pesquisa(palavra, arv->NO.NoInterno.Esq, qtdBusca);
    }else{
        return pesquisa(palavra, arv->NO.NoInterno.Dir, qtdBusca);
    }
}
//coleta os dados como quantos documentos a palavra aparece e calcula o peso e acumula por documento 
void calcular_peso(TipoArvore arv, char *palavra, int n, double soma[], int *qtdBusca){
    TipoArvore noDaPalavra = pesquisa(palavra, arv, qtdBusca);

    if (noDaPalavra == NULL) return;

    int dj = 0;
    // atual recebe a folha que retornou da função de pesquisa para poder saber quantos documentos possui essa palavra
    Celula* atual = noDaPalavra->NO.NoFolha.Lista.primeiro;

    while (atual != NULL)
    {
       dj++;
       atual = atual->prox;
    }
    
    atual = noDaPalavra->NO.NoFolha.Lista.primeiro;
//comeca a preencher o vetor com o resultado do calculo onde o indice representa o iddoc
    while (atual != NULL)
    {
        double w = atual->qtde * (log2((double)n) / dj);
        soma[atual->idDoc] += w;
        atual = atual->prox;
    }
    


}
//cria o vetor e ordena por relevancia de acordo com o resultado do calculo 
int tfidf_patricia(TipoArvore arv, char **palavras, int qtdPalavras, int n, int *ni, prioridade *resultados, int *qtdBusca){
    //cria o vetor que sera responsavel por receber os resultados parciais do calculo
    double *soma = calloc(n, sizeof(double));
    int i;

    for (i=0; i< qtdPalavras; i++){
        calcular_peso(arv, palavras[i], n, soma, qtdBusca);
    }

    int quantidadeRel = 0;
//ocorre a preparação do dado para poder ser ordenado de acordo com o seu valor e finalização do calculo
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
//Percorre o vetor de resultados e imprime o ranking dos documentos nome, título e relevância na tela.
void imprimirRel_patricia(prioridade *resultados, int quantosrel, Corpus *corpus){
    for(int i=0; i< quantosrel; i++){
        printf("%s - %s -- Relevância %.2f\n",
        corpus->nomes[resultados[i].iddoc],
        corpus->titulos[resultados[i].iddoc],
        resultados[i].valor);
    }
}

