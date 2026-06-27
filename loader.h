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
#define MAX_DOCS 20
#define MAX_CAMINHO 256
#define DIR_FABULAS "Fabulas/"
#define MAX_CAMINHO_COMPLETO (MAX_CAMINHO + 8)  // 8 = strlen("Fabulas/")
typedef struct {
    char palavra[MAX_PALAVRA];
    int idDoc;
} Token;

typedef struct {
    Token *tokens;
    char nomes[MAX_DOCS][MAX_PALAVRA];
    char titulos[MAX_DOCS][MAX_PALAVRA];
    int qtdDocs;
    int tamanho;
    int capacidade;
} Corpus;

int isStopWord(char *palavra);
void normalizar(char *str);
void removerPontuacao(char *str);
void adicionarToken(Corpus *c, char *palavra, int idDoc);
Corpus carregarCorpus();

#endif
