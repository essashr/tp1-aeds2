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

#ifndef TFIDF_PATRICIA_H
#define TFIDF_PATRICIA_H

#include "patricia.h"

typedef struct {
    double valor;
    int iddoc;
}prioridade;

int consulta_dj(char *palavra, TipoArvore arv);

void calcular_prioridade(TipoArvore arv, int v[], int n, char *palavra, prioridade pri[]);

void impressão_relevancia(prioridade pri[], int n);

/*arthur, vou deixar assim pq é como eu to usando no tfidf hash e como to chamando no main*/
int tfidf_patricia(TipoArvore arv, char **palavras, int qtdPalavras, int n, int *ni, prioridade *resultados);
void imprimirRel_patricia(prioridade *resultados, int quantosrel, Corpus *corpus);

int compara_prioridade(const void *a, const void *b);

#endif