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

#include "loader.h"
#include "hash/indice_hash.h"
#include "hash/tfidf_hash.h"
#include "patricia/indice_patricia.h"
#include "patricia/tfidf_patricia.h"

static char **lerTermos(int *qtdTermos) {
    printf("Quantos termos de busca? ");
    scanf("%d", qtdTermos);

    char **termos = malloc(*qtdTermos * sizeof(char *));
    for (int i = 0; i < *qtdTermos; i++) {
        termos[i] = malloc(MAX_PALAVRA * sizeof(char));
        printf("Termo %d: ", i + 1);
        scanf("%49s", termos[i]);
        normalizar(termos[i]);
        removerPontuacao(termos[i]);
    }
    return termos;
}

static void liberarTermos(char **termos, int qtd) {
    for (int i = 0; i < qtd; i++)
        free(termos[i]);
    free(termos);
}

/* =======================================================================
 * main
 * Menu conforme Tarefa 5 do enunciado:
 *   a) carregar corpus
 *   b) construir índices (HASH e PATRICIA)
 *   c) imprimir índices (individualmente)
 *   d) buscar por termos (individualmente)
 * ======================================================================= */
int main() {
    Corpus corpus;
    TabelaHash h;
    TipoArvore patricia = NULL;
    int ni[MAX_DOCS] = {0};

    int corpusCarregado  = 0;
    int indicesConstruidos = 0;

    int qtdComparacoesPatricia = 0;
    int qtdComparacoesBuscaPatricia = 0;

    int opcao;
    do {
        printf("\n=== Menu ===\n");
        printf("1. Carregar corpus\n");
        printf("2. Construir indices invertidos (HASH e PATRICIA)\n");
        printf("3. Imprimir indice - HASH\n");
        printf("4. Imprimir indice - PATRICIA\n");
        printf("5. Buscar fabulas - HASH\n");
        printf("6. Buscar fabulas - PATRICIA\n");
        printf("0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {

            /* ---------------------------------------------------------
             * a) Carregar corpus
             * --------------------------------------------------------- */
            case 1:
                corpus = carregarCorpus();
                corpusCarregado = 1;
                printf("Corpus carregado: %d tokens, %d documentos.\n",
                       corpus.tamanho, corpus.qtdDocs);
                break;

            /* ---------------------------------------------------------
             * b) Construir índices
             * --------------------------------------------------------- */
            case 2:
                if (!corpusCarregado) {
                    printf("Carregue o corpus primeiro (opcao 1).\n");
                    break;
                }

                /* Hash */
                inicializarHash(&h);
                construirIndiceHash(&h, &corpus);

                /* Patricia */
                patricia = NULL;
                for (int i = 0; i < corpus.tamanho; i++)
                    Insere(corpus.tokens[i], &patricia, &qtdComparacoesPatricia);


                /* ni — calculado a partir da hash (O(n), sem duplicatas) */
                calcularNi(&h, ni, corpus.qtdDocs);

                indicesConstruidos = 1;
                printf("Indices construidos com sucesso.\n");
                printf("Comparacoes de insercao (PATRICIA): %d\n",
                       qtdComparacoesPatricia);
                printf("Comparacoes de insercao (HASH): %ld\n", h.totalComparacoesInsercao);
                break;

            /* c) Imprimir índice HASH */
            case 3:
                if (!indicesConstruidos) {
                    printf("Construa os indices primeiro (opcao 2).\n");
                    break;
                }
                printf("\n--- Indice Invertido (HASH) ---\n");
                imprimirIndiceHash(&h);
                break;

            /*c) Imprimir índice PATRICIA */
            case 4:
                if (!indicesConstruidos) {
                    printf("Construa os indices primeiro (opcao 2).\n");
                    break;
                }
                printf("\n--- Indice Invertido (PATRICIA) ---\n");
                imprime_indice_patricia(patricia);
                break;

            /* d) Buscar — HASH */
            case 5:
                if (!indicesConstruidos) {
                    printf("Construa os indices primeiro (opcao 2).\n");
                    break;
                }
                {
                    int qtd;
                    char **termos = lerTermos(&qtd);
                    ResultadosRel resultados[MAX_DOCS];
                    h.totalComparacoesBusca = 0;
                    int quantosrel = tfidf(&h, termos, qtd,
                                          corpus.qtdDocs, ni, resultados);
                    printf("\n--- Resultados (HASH) ---\n");
                    if (quantosrel == 0)
                        printf("Nenhuma fabula encontrada.\n");
                    else
                        imprimirRel(resultados, quantosrel, &corpus);
                    printf("Comparacoes de busca (HASH): %ld\n",
                           h.totalComparacoesBusca);
                    liberarTermos(termos, qtd);
                }
                break;

            /* ---------------------------------------------------------
             * d) Buscar — PATRICIA
             * --------------------------------------------------------- */
            case 6:
                if (!indicesConstruidos) {
                    printf("Construa os indices primeiro (opcao 2).\n");
                    break;
                }
                {
                    int qtd;
                    char **termos = lerTermos(&qtd);
                    prioridade resultados[MAX_DOCS];
                    qtdComparacoesBuscaPatricia = 0;
                    int quantosrel = tfidf_patricia(patricia, termos, qtd,
                                                   corpus.qtdDocs, ni, resultados, &qtdComparacoesBuscaPatricia);
                    printf("\n--- Resultados (PATRICIA) ---\n");
                    if (quantosrel == 0){
                        printf("Nenhuma fabula encontrada.\n");
                    }else {
                        imprimirRel_patricia(resultados, quantosrel, &corpus);
                        }
                    liberarTermos(termos, qtd);
                }
                printf("Comparacoes de busca (PATRICIA): %d\n", qtdComparacoesBuscaPatricia);
                break;

            case 0:
                break;

            default:
                printf("Opcao invalida.\n");
        }

    } while (opcao != 0);

    if (indicesConstruidos){
        liberarHash(&h);
        liberarPatricia(&patricia);}
    if (corpusCarregado){
        free(corpus.tokens);
    }

    return 0;
}