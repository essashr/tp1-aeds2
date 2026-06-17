#include "../lista.h"
#include "../loader.h"
#include "hash.h"




void comparar(const void*a, const void*b){
    EntradaHash *ea = *(EntradaHash **)a;
    EntradaHash *eb = *(EntradaHash **)b;
    return(strcmp(ea->palavra, eb->palavra));
}



void construirIndiceHash(TabelaHash *h, Corpus *corpus){
    for(int i = 0; i < corpus->tamanho; i++){
        inserirHash(h, corpus->tokens[i].palavra, corpus->tokens[i].idDoc);
    }
}

void imprimirIndiceHash(TabelaHash *h, Corpus arquivozao){
    EntradaHash *entradas[5000];
    int n = 0;
    
    for(int i = 0; i < M; i++){
        EntradaHash *atual = h->tabela[i];
        while(atual != NULL){
            entradas[n] = atual;
            n++;
            atual = atual->prox;
        }
    }
    


    qsort(entradas, n, sizeof(EntradaHash *), comparar);

    for(int i = 0; i < n; i++){
        printf("%s\n", entradas[i]->palavra);
        
    }
}