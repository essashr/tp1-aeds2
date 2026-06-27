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

#ifndef INDICE_HASH_H
#define INDICE_HASH_H
#include "hash.h"

void construirIndiceHash(TabelaHash *h, Corpus *corpus);
void imprimirIndiceHash(TabelaHash *h);

// compara para usar depois no qsort
int comparar(const void *a, const void *b);

// calcula ni a partir da Tabela Hash
void calcularNi(TabelaHash *h, int *ni, int qtdDocs);

#endif