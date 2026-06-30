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

#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../lista.h"
#include "../loader.h"


/*
 * Tamanho da tabela hash.
 *
 * Justificativa do fator de carga:
 *   - Tokens totais (sem stopwords) = 621.
 *   - Palavras únicas (vocabulário) = 395.
 *   - Fator de carga alvo: α = 0.75  →  M = 395 / 0.75 ≈ 526.
 *   - Escolhemos o primo mais próximo acima: M = 541.
 */
#define M 541

#ifndef MAX_PALAVRA
#define MAX_PALAVRA 50
#endif

/* -----------------------------------------------------------------------
 * Nó do encadeamento externo (colisões na mesma posição da tabela).
 * Cada nó armazena uma palavra e a lista de ocorrências nos documentos.
 * ----------------------------------------------------------------------- */
typedef struct EntradaHash {
    char palavra[MAX_PALAVRA];
    ListaOcorrencias  ocorrencias;
    struct EntradaHash *prox; /* próxima entrada na mesma posição (colisão) */
} EntradaHash;

/* -----------------------------------------------------------------------
 * Tabela hash principal.
 * tabela[i] aponta para a lista encadeada de entradas na posição i.
 * Os contadores servem para a análise comparativa (solicitado na Tarefa 6 do pdf).
 * ----------------------------------------------------------------------- */
typedef struct {
    EntradaHash *tabela[M];
    long totalComparacoesInsercao; /* comparações acumuladas nas inserções */
    long totalComparacoesBusca;    /* comparações acumuladas nas buscas */
} TabelaHash;

int hashcode(const char *palavra);
void inicializarHash(TabelaHash *h);

/*
 * Insere a palavra na tabela (ou incrementa a ocorrência se já existir)
 * associando-a ao documento idDoc.
 */
void inserirHash(TabelaHash *h, const char *palavra, int idDoc);

/*
 * Busca a palavra na tabela.
 * Retorna ponteiro para a EntradaHash encontrada, ou NULL se não existir.
 */
EntradaHash *buscarHash(TabelaHash *h, const char *palavra);

void liberarHash(TabelaHash *h);

#endif