#include "hash.h"




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



 int calculaPesoTermo(char * palavra, TabelaHash *h){
    int idx = hashcode(palavra);
    int dj = contadj(h,&palavra);
    int fdji = h->tabela[idx]->ocorrencias.primeiro->qtde;
    

 }
