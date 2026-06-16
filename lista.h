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

#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Celula {
    int idDoc;
    int qtde;
    struct Celula *prox;
} Celula;

typedef struct {
    Celula *primeiro;
    Celula *ultimo;
} ListaOcorrencias;

void inicializarLista(ListaOcorrencias *lista);
void inserirOcorrencia(ListaOcorrencias *lista, int idDoc);
void imprimirLista(ListaOcorrencias *lista);
void liberarLista(ListaOcorrencias *lista);

#endif
