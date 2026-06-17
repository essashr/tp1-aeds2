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


#include "hash.h"
#include "../loader.h"
/* hashcode
 *
 * Função de hash polinomial (variante Horner):
 *   h = (h * base + c) para cada caractere c da palavra.
 */
int hashcode(const char *palavra) {
    unsigned long h = 0;
    const int base = 31;

    for (int i = 0; palavra[i] != '\0'; i++)
        h *= base + (unsigned char)palavra[i];

    return (int)(h % M);
}

/* inicializarHash
 *
 * Coloca NULL em todas as posições da tabela e zera os contadores de
 * comparações usados na análise de desempenho.
 */
void inicializarHash(TabelaHash *h) {
    for (int i = 0; i < M; i++){
        h->tabela[i] = NULL;
        h->tabela[i]->qtdeDoc = 0;
    }   
    h->totalComparacoesInsercao = 0;
    h->totalComparacoesBusca    = 0;
}


/* =======================================================================
 * inserirHash
 *
 * Algoritmo:
 *   1. Calcula o índice com hashcode().
 *   2. Percorre a lista encadeada na posição procurando a palavra.
 *      - Se encontrar: roda a inserirOcorrencia() da lista, que
 *        incrementa qtde do documento ou cria nova célula.
 *      - Se não encontrar: aloca nova EntradaHash, inicializa a lista
 *        de ocorrências e a insere na cabeça da lista (O(1)).
 * ======================================================================= */
void inserirHash(TabelaHash *h, const char *palavra, int idDoc, Corpus c) {
    int idx   = hashcode(palavra);
    EntradaHash *atual = h->tabela[idx];


    /* Percorre a lista encadeada na posição idx */
    while (atual != NULL) {
        h->totalComparacoesInsercao++; /* conta a comparação */
        if (strcmp(atual->palavra, palavra) == 0) {
            /* Palavra já existe: registra mais uma ocorrência */
            inserirOcorrencia(&atual->ocorrencias, idDoc);
            return;
        }

        atual = atual->prox;
    }

    /* Palavra nova: cria entrada e insere na cabeça da lista */
    EntradaHash *nova = (EntradaHash *)malloc(sizeof(EntradaHash));
    // AQUI ENTRA O VETOR PARA INDICAR O "NI" DA TFIDF
    int vetoriDsDoc[c.tamanho];
    if (!nova) {
        printf("Erro: falha ao alocar EntradaHash para \"%s\"\n", palavra);
        return;
    }



    strncpy(nova->palavra, palavra, MAX_PALAVRA - 1);
    nova->palavra[MAX_PALAVRA - 1] = '\0';

    inicializarLista(&nova->ocorrencias);
    inserirOcorrencia(&nova->ocorrencias, idDoc);
    h->tabela[idx]->qtdeDoc++;    // incrementa para indicar que tem +1 idDoc naquela lista de Ocorrencias      


    /* Inserção na cabeça: nova->prox aponta para quem estava antes */
    nova->prox = h->tabela[idx];
    h->tabela[idx] = nova;
}

/* =======================================================================
 * buscarHash
 *
 * Calcula o índice e percorre a lista encadeada comparando palavras.
 * Retorna ponteiro para a EntradaHash se encontrar, NULL caso contrário.
 * Cada strcmp conta para totalComparacoesBusca (análise Tarefa 6).
 * ======================================================================= */
EntradaHash *buscarHash(TabelaHash *h, const char *palavra) {
    int idx = hashcode(palavra);
    EntradaHash *atual = h->tabela[idx];

    while (atual != NULL) {
        h->totalComparacoesBusca++; /* conta a comparação */

        if (strcmp(atual->palavra, palavra) == 0)
            return atual; /* encontrou */

        atual = atual->prox;
    }

    return NULL; /* não encontrou */
}

/* liberarHash
 *
 * Percorre todos os slots, libera cada EntradaHash (e sua lista interna)
 * e redefine o ponteiro do slot para NULL.
 */
void liberarHash(TabelaHash *h) {
    for (int i = 0; i < M; i++) {
        EntradaHash *atual = h->tabela[i];

        while (atual != NULL) {
            EntradaHash *prox = atual->prox;
            liberarLista(&atual->ocorrencias);
            free(atual);
            atual = prox;
        }

        h->tabela[i] = NULL;
    }

    h->totalComparacoesInsercao =0;
    h->totalComparacoesBusca =0;
}