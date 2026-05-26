#ifndef LOADER_H
#define LOADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_PALAVRA 50
#define MAX_CAMINHO 100

typedef struct {
    char palavra[MAX_PALAVRA];
    int idDoc;
} Token;

typedef struct {
    Token* tokens;
    int tamanho;
    int capacidade;
} Corpus;

extern const char *stopwords[];
extern const int stopwords_count;
int isStopWord(char *palavra);
void normalizar(char *str);
void removerPontuacao(char *str);
void adicionarToken(Corpus *c, char *palavra, int idDoc);
Corpus carregarCorpus();

#endif