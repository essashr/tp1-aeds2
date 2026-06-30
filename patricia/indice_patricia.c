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

#include "indice_patricia.h"

//Percorre imprimindo cada idDoc e a quantidade que a palavra se repetiu dentro dele
void imprime_lista_ocorrencias(ListaOcorrencias lista){
    Celula *atual = lista.primeiro;
    while (atual != NULL)
    {
        printf("<%d, %d> ", atual->qtde, atual->idDoc);
        atual = atual->prox;
    }
}

//Percorre a arvore imprimindo todas as palavras e seus respectivos idDoc com a quantidade que ela se repetiu
void imprime_indice_patricia(TipoArvore arv){
    if (arv == NULL)
        return;
    if (arv->nt == Interno){
        imprime_indice_patricia(arv->NO.NoInterno.Esq);
        imprime_indice_patricia(arv->NO.NoInterno.Dir);
    }

    else if (arv->nt == Externo){
        printf("%s\n", arv->NO.NoFolha.Chave);
        imprime_lista_ocorrencias(arv->NO.NoFolha.Lista);
        printf("\n");
    }
}