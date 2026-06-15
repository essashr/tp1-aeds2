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

#ifndef PATRICIA_H
#define PATRICIA_H
#include <stdio.h>
#include <stdlib.h>
#include "././loader.h"
#include "./LISTA_ENCADEADA/lista_encadeada.h"

#define D 8
typedef char TipoChave[MAX_PALAVRA];
typedef unsigned char TipoIndexAmp;
typedef unsigned char TipoDib;

typedef enum {
    Interno, Externo
} TipoNo;

typedef struct TipoPatNo* TipoArvore;
typedef struct TipoPatNo {
    TipoNo nt;
    union
    {
        struct {
            TipoIndexAmp Index;
            TipoArvore Esq, Dir;
        } NoInterno;
        struct {
            TipoChave Chave;
            ListaDeIDs Lista;
        } NoFolha;
    } NO;
    
} TipoPatNo;

#endif