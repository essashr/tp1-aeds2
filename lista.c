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

#include "lista.h"

void inicializarLista(ListaOcorrencias *lista) {
    lista->primeiro = NULL;
    lista->ultimo   = NULL;
}

/* Percorre a lista procurando o idDoc:
 * se encontrar, incrementa qtde.
 * se não encontrar, cria célula nova no final (mantém ordem por idDoc de inserção).*/
void inserirOcorrencia(ListaOcorrencias *lista, int idDoc) {
    /* Procura se o documento já tem entrada na lista */
    Celula *atual = lista->primeiro;

    while (atual != NULL) {
        if (atual->idDoc == idDoc) {
            atual->qtde++;
            return;
        }
        atual = atual->prox;
    }

    /* Documento ainda não está na lista, então cria célula nova */
    Celula *nova = (Celula *)malloc(sizeof(Celula));

    if (!nova) {
        printf("Erro: falha ao alocar célula da lista\n");
        return;
    }

    nova->idDoc = idDoc;
    nova->qtde  = 1;
    nova->prox  = NULL;

    if (lista->primeiro == NULL) {
        lista->primeiro = nova;
        lista->ultimo   = nova;
    } else {
        lista->ultimo->prox = nova;
        lista->ultimo       = nova;
    }
}

/* Imprime a lista igual o enunciado */
void imprimirLista(ListaOcorrencias *lista) {
    Celula *atual = lista->primeiro;

    while (atual != NULL) {
        printf("<%d, %d>", atual->qtde, atual->idDoc);
        if (atual->prox != NULL)
            printf(" ");
        atual = atual->prox;
    }
}

/* Limpa a lista e libera a memória alocada */
void liberarLista(ListaOcorrencias *lista) {
    Celula *atual = lista->primeiro;

    while (atual != NULL) {
        Celula *prox = atual->prox;
        free(atual);
        atual = prox;
    }

    lista->primeiro = NULL;
    lista->ultimo   = NULL;
}
