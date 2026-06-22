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

#include "lista.h"


/*
 * Tamanho da tabela hash.
 *
 * Justificativa do fator de carga:
 *   - Tokens totais (sem stopwords) = 493.
 *   - Palavras únicas (vocabulário) = 316.
 *   - Fator de carga alvo: α = 0.75  →  M = 316 / 0.75 ≈ 421.
 *   - Escolhemos o primo mais próximo acima: M = 431.
 */
#define M 431

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
    int qtdeDoc;
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

/* Calcula o índice hash de uma palavra usando função polinomial (Horner). */
int hashcode(const char *palavra);

/* Inicializa todos os slots da tabela com NULL e zera os contadores. */
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

int contadj(TabelaHash *h, char *palavra);

/* Libera toda a memória alocada pela tabela. */
void liberarHash(TabelaHash *h);

#endif