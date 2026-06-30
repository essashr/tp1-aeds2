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


#define MAX_PALAVRA      20   // maior palavra medida: 15 ("insignificantes")
#define MAX_NOME         16   // maior nome medido: 12 ("fabula20.txt")
#define MAX_TITULO       50   // maior título medido: 35 ("O Rato do Campo e o Rato da Cidade")
#define MAX_CAMINHO      32   // MAX_NOME + strlen("Fabulas/") = 12 + 8 = 20
#define MAX_DOCS         20
#define DIR_FABULAS      "Fabulas/"

/* um token é uma palavra já pré-processada com o id do documento de origem */
typedef struct {
    char palavra[MAX_PALAVRA];
    int idDoc;
} Token;

/* corpus completo: vetor dinâmico de tokens + dados dos documentos */
typedef struct {
    Token *tokens;                      /* palavras indexáveis de todas as fábulas */
    char nomes[MAX_DOCS][MAX_NOME];     /* nomes dos arquivos, indexados por idDoc */
    char titulos[MAX_DOCS][MAX_TITULO]; /* primeira linha de cada fábula (título) */
    int qtdDocs;                        /* quantidade de documentos carregados */
    int tamanho;                        /* total de tokens no corpus */
    int capacidade;                     /* capacidade atual do vetor de tokens */
} Corpus;

int isStopWord(char *palavra);
void normalizar(char *str);
void removerPontuacao(char *str);
void adicionarToken(Corpus *c, char *palavra, int idDoc);
Corpus carregarCorpus();

#endif