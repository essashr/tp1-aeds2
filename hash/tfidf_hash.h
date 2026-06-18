#include "../loader.h"
#include "hash.h"


typedef struct{
    int idDoc;
    double relevancia;
} ResultadosRel;


 void pesosTermo(char * palavra, TabelaHash *h, int v[], int n, double soma[]);

int tfidf(TabelaHash *h, char **palavra, int qtdPalavras, int n, int *ni, ResultadosRel *resultados);

int cmpRel(const void *a, const void *b);
 
void imprimirRel(ResultadosRel *resultados);



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

