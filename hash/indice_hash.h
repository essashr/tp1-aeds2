#ifndef INDICE_HASH_H
#define INDICE_HASH_H
#include "hash.h"
#include "../loader.h"

void construirIndiceHash(TabelaHash *h, Corpus *corpus);
void imprimirIndiceHash(TabelaHash *h);

/*
* COMPARA PARA SER USADO NO QSORT
*/
void comparar(const void*a, const void*b);



#endif
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

