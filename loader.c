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

static const char *stopwords[] = {
    "de", "a", "o", "que", "e", "do", "da", "em", "um", "para",
    "com", "nao", "uma", "os", "no", "se", "na", "por", "mais", "as",
    "dos", "como", "mas", "foi", "ao", "ele", "das", "tem", "seu", "sua",
    "ou", "ser", "quando", "muito", "ha", "nos", "ja", "esta", "eu", "tambem",
    "so", "pelo", "pela", "ate", "isso", "ela", "entre", "era", "depois", "sem",
    "mesmo", "aos", "ter", "seus", "quem", "nas", "me", "esse", "eles", "estao",
    "voce", "tinha", "foram", "essa", "num", "nem", "suas", "meu", "minha", "numa",
    "pelos", "elas", "havia", "seja", "qual", "sera", "tenho", "lhe", "deles", "essas",
    "esses", "pelas", "este", "fosse", "dele", "tu", "te", "voces", "vos", "lhes",
    "meus", "minhas", "teu", "tua", "teus", "tuas", "nosso", "nossa", "nossos", "nossas",
    "dela", "delas", "estes", "estas", "aquele", "aquela", "aqueles", "aquelas", "isto", "aquilo",
    "estou", "estamos", "estive", "esteve", "estivemos", "estiveram", "estava", "estavamos", "estavam", "estivera",
    "estiveramos", "esteja", "estejamos", "estejam", "estivesse", "estivessemos", "estivessem", "estiver", "estivermos", "estiverem",
    "havemos", "houve", "houvemos", "houveram", "houvera", "houveramos", "haja", "hajamos", "hajam", "houvesse",
    "houvessemos", "houvessem", "houver", "houvermos", "houverem", "houverei", "houveremos", "houverao", "houveria", "houveriamos",
    "houveriam", "sou", "somos", "sao", "eramos", "eram", "fui", "fomos", "fora", "foramos",
    "sejamos", "sejam", "fossemos", "fossem", "for", "formos", "forem", "serei", "seremos", "serao",
    "seria", "seriamos", "seriam", "temos", "tinhamos", "tinham", "tive", "teve", "tivemos", "tiveram",
    "tivera", "tiveramos", "tenha", "tenhamos", "tenham", "tivesse", "tivessemos", "tivessem", "tiver", "tivermos",
    "tiverem", "terei", "tera", "teremos", "terao", "teria", "teriamos", "teriam"
};

/* verifica se a palavra é uma stop word (preposição, artigo ou conjunção) */
int isStopWord(char *palavra) {
    int n = sizeof(stopwords) / sizeof(stopwords[0]);

    for (int i = 0; i < n; i++) {
        if (strcmp(palavra, stopwords[i]) == 0)
            return 1;
    }

    return 0;
}

/* converte todos os caracteres para minúsculas */
void normalizar(char *str) {
    for (int i = 0; str[i]; i++)
        str[i] = tolower(str[i]);
}

/* remove tudo que não for letra (pontuação, números) */
void removerPontuacao(char *str) {
    int j = 0;

    for (int i = 0; str[i]; i++) {
        if (isalpha(str[i]))
            str[j++] = str[i];
    }

    str[j] = '\0';
}

/* adiciona um token ao corpus, dobrando a capacidade via realloc se necessário */
void adicionarToken(Corpus *c, char *palavra, int idDoc) {
    if (c->tamanho == c->capacidade) {
        c->capacidade *= 2;
        Token *tmp = realloc(c->tokens, c->capacidade * sizeof(Token));

        if (!tmp) {
            printf("Erro: falha ao realocar memória para tokens\n");
            return;
        }

        c->tokens = tmp;
    }

    strcpy(c->tokens[c->tamanho].palavra, palavra);
    c->tokens[c->tamanho].idDoc = idDoc;
    c->tamanho++;
}

Corpus carregarCorpus() {
    Corpus c;
    c.tamanho = 0;
    c.capacidade = 100;
    c.qtdDocs = 0;
    c.tokens = malloc(c.capacidade * sizeof(Token));

    FILE *entrada = fopen(DIR_FABULAS "entrada.txt", "r");

    if (!entrada) {
        printf("Erro ao abrir entrada.txt\n");
        exit(1);
    }

    int qtdArquivos;
    fscanf(entrada, "%d", &qtdArquivos);

    char nomeArquivo[MAX_NOME];

    for(int idDoc = 0; idDoc < qtdArquivos; idDoc++) {
        fscanf(entrada, "%s", nomeArquivo);
        strcpy(c.nomes[idDoc], nomeArquivo);
        c.qtdDocs++;

        char caminhoCompleto[MAX_CAMINHO];
        snprintf(caminhoCompleto, sizeof(caminhoCompleto), DIR_FABULAS "%s", nomeArquivo);

        FILE *fabula = fopen(caminhoCompleto, "r");

        if (!fabula) {
            printf("Aviso: nao foi possivel abrir %s, pulando...\n", caminhoCompleto);
            continue;
        }
        /* lê o título antes do loop de tokens — fgets consome a linha,
        então o fscanf abaixo começa já do conteúdo da fábula */
        fgets(c.titulos[idDoc], MAX_CAMINHO, fabula);
        int len = strlen(c.titulos[idDoc]);
        if (len > 0 && c.titulos[idDoc][len - 1] == '\n')
            c.titulos[idDoc][--len] = '\0';
        if (len > 0 && c.titulos[idDoc][len - 1] == '\r')
            c.titulos[idDoc][--len] = '\0';

        char palavra[MAX_PALAVRA];

        while (fscanf(fabula, "%49s", palavra) == 1) {
            normalizar(palavra);
            removerPontuacao(palavra);

            if (strlen(palavra) == 0)
                continue;

            if (isStopWord(palavra))
                continue;

            adicionarToken(&c, palavra, idDoc);
        }

        fclose(fabula);
    }

    fclose(entrada);
    return c;
}
