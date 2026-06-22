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

#ifndef LOADER_H
#define LOADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_PALAVRA 50
#define MAX_CAMINHO 256
#define DIR_FABULAS "Fabulas/"

typedef struct {
    char palavra[MAX_PALAVRA];
    int idDoc;
} Token;

typedef struct {
    Token *tokens;
    int tamanho;
    int capacidade;
<<<<<<< HEAD
    int *v_total;
    
=======
    int * v_total;
>>>>>>> 545adccd5568747d67febbc444093e6f6f0033e4
} Corpus;

int isStopWord(char *palavra);
void normalizar(char *str);
void removerPontuacao(char *str);
void adicionarToken(Corpus *c, char *palavra, int idDoc);
Corpus carregarCorpus();

#endif
