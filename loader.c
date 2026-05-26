#include "loader.h"

const char *stopwords[] = {
    "a", "o", "e", "de", "da", "do",
    "em", "um", "uma", "para", "com"
};

int isStopWord(char *palavra) {
    int n = sizeof(stopwords)/sizeof(stopwords[0]);

    for(int i = 0; i < n; i++) {
        if(strcmp(palavra, stopwords[i]) == 0) {
            return 1;
        }
    }

    return 0;
}

void normalizar(char *str) {
    for(int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

void removerPontuacao(char *str) {
    int j = 0;

    for(int i = 0; str[i]; i++) {
        if(isalpha(str[i])) {
            str[j++] = str[i];
        }
    }

    str[j] = '\0';
}

void adicionarToken(Corpus *c, char *palavra, int idDoc) {
    if(c->tamanho == c->capacidade) {

        c->capacidade *= 2;

        c->tokens = realloc(
            c->tokens,
            c->capacidade * sizeof(Token)
        );
    }

    strcpy(c->tokens[c->tamanho].palavra, palavra);
    c->tokens[c->tamanho].idDoc = idDoc;

    c->tamanho++;
}

Corpus carregarCorpus() {

    Corpus c;

    c.tamanho = 0;
    c.capacidade = 100;

    c.tokens = malloc(c.capacidade * sizeof(Token));

    FILE *entrada = fopen("Fabulas/entrada.txt", "r");

    if(!entrada) {
        printf("Erro ao abrir entrada.txt\n");
        exit(1);
    }

    int qtdArquivos;

    fscanf(entrada, "%d", &qtdArquivos);

    char nomeArquivo[MAX_CAMINHO];

    for(int idDoc = 0; idDoc < qtdArquivos; idDoc++) {

        fscanf(entrada, "%s", nomeArquivo);

        char caminhoCompleto[150];

        sprintf(
            caminhoCompleto,
            "Fabulas/%s",
            nomeArquivo
        );

        FILE *fabula = fopen(caminhoCompleto, "r");

        if(!fabula) {
            printf("Erro ao abrir %s\n", caminhoCompleto);
            continue;
        }

        char palavra[MAX_PALAVRA];

        while(fscanf(fabula, "%49s", palavra) == 1) {

            normalizar(palavra);

            removerPontuacao(palavra);

            if(strlen(palavra) == 0)
                continue;

            if(ehStopWord(palavra))
                continue;

            adicionarToken(&c, palavra, idDoc);
        }

        fclose(fabula);
    }

    fclose(entrada);

    return c;
}