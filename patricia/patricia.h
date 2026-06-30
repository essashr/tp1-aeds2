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
#include <string.h>
#include <math.h>
#include "../loader.h"
#include "../lista.h"

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
    union //Se o no for interno ele armazenara o index que difere, ponteiro para o lado direito e esquerdo e o caracter menor que diferiu. Se o no for externo irá armazenar a chave (palavra) e uma lista de ocorrencias (que lida e armazena os iddocs quando a palavra se repete na inserção)
    {
        struct {
            TipoIndexAmp Index;
            TipoArvore Esq, Dir;
            char indexCaracter;
        } NoInterno;
        struct {
            TipoChave Chave;
            ListaOcorrencias Lista;
            int qtddoc;
        } NoFolha;
    } NO;
    
} TipoPatNo;



short EExterno (TipoArvore p);
void criarListaNo (ListaOcorrencias * lista);
TipoArvore CriaNoInt (int i, TipoArvore *Esq, TipoArvore *Dir, char caracter);
TipoArvore CriaNoExt (char *palavra);
int CompararPalavras (char *palavra, char *palavraArvore, int *qtdComp);
TipoArvore InsereEntre (Token informacao, TipoArvore *t, int i, char caracterArv, int *qtdComp);
TipoArvore Insere (Token informacao, TipoArvore *t, int *qtdcomparacoes);
void liberarPatricia(TipoArvore *t);
#endif