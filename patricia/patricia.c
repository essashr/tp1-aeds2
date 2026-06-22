#include "patricia.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Funções auxiliares 
short EExterno (TipoArvore p){
    return (p->nt == Externo);
}

void criarListaNo (ListaOcorrencias * lista){
    inicializarLista(lista);
}

//Criar Nós Interno e Externo
TipoArvore CriaNoInt (int i, TipoArvore *Esq, TipoArvore *Dir, char caracter){
    TipoArvore p;
    p = (TipoArvore)malloc(sizeof(TipoPatNo));
    p->nt = Interno; p->NO.NoInterno.Esq = *Esq;
    p->NO.NoInterno.Dir = *Dir;
    p->NO.NoInterno.Index = i;
    p->NO.NoInterno.indexCaracter = caracter;
    return p;
}

TipoArvore CriaNoExt (char *palavra){
    TipoArvore p;
    p = (TipoArvore)malloc(sizeof(TipoPatNo));
    p->nt = Externo;
    strcpy(p->NO.NoFolha.Chave, palavra);
    return p;
}

//Algoritmo que compara as palavras
int CompararPalavras (char *palavra, char *palavraArvore){
    int i = 0;
    while (palavra[i] == palavraArvore[i]){

        i++;

        if (palavra[i] == '\0' && palavraArvore[i] == '\0'){
            return -1;
        }
    } 
    return i;
}

//Imprimir arvore
void imprimir(TipoArvore t){
    if (t == NULL){
        return;
    }
    if (EExterno(t)){
        printf("%s\n", t->NO.NoFolha.Chave);
    } else {
        printf("Index %d Caracter %c\n", t->NO.NoInterno.Index, t->NO.NoInterno.indexCaracter);
        imprimir(t->NO.NoInterno.Esq);
        imprimir(t->NO.NoInterno.Dir);
    }
}

//Algoritmo de Inserção 
TipoArvore InsereEntre (Token informacao, TipoArvore *t, int i){
    TipoArvore p;
    if (EExterno(*t) || i < (*t)->NO.NoInterno.Index){
        p = CriaNoExt(informacao.palavra);
        // criarListaNo(&p->NO.NoFolha.Lista);
        // inserirOcorrencia(&p->NO.NoFolha.Lista, idDoc);
        if (!EExterno(*t)){
                if (informacao.palavra[i] < (*t)->NO.NoInterno.indexCaracter){//O if está analisando um nó que é interno
                    *t = CriaNoInt(i, &p, t, informacao.palavra[i]);
                    return *t;
                } else {
                    *t = CriaNoInt(i, t, &p, (*t)->NO.NoInterno.indexCaracter);
                    return *t;
                }
        } else {
            if (informacao.palavra[i] < (*t)->NO.NoFolha.Chave[i]){//Já aqui o if está analisando um nó que é externo
                if (informacao.palavra[i] == '\0'){
                        *t = CriaNoInt(i, &p, t, (*t)->NO.NoFolha.Chave[i]);
                        return *t;
                    } else {
                        *t = CriaNoInt(i, &p, t, informacao.palavra[i]);
                        return *t; 
                    }
                } else {
                    if ((*t)->NO.NoFolha.Chave[i] == '\0'){
                        *t = CriaNoInt(i, t, &p, informacao.palavra[i]); 
                        return *t;
                    } else {
                        *t = CriaNoInt(i, t, &p, (*t)->NO.NoFolha.Chave[i]);
                        return *t;
                    }
                }
        }
        

    } else {
        if (informacao.palavra[(*t)->NO.NoInterno.Index] < (*t)->NO.NoInterno.indexCaracter){
            (*t)->NO.NoInterno.Esq = InsereEntre(informacao, &(*t)->NO.NoInterno.Esq, i);

        } else if (informacao.palavra[(*t)->NO.NoInterno.Index] > (*t)->NO.NoInterno.indexCaracter){
            (*t)->NO.NoInterno.Dir = InsereEntre(informacao, &(*t)->NO.NoInterno.Dir, i);

        } else if (informacao.palavra[(*t)->NO.NoInterno.Index] == (*t)->NO.NoInterno.indexCaracter){
            if (((*t)->NO.NoInterno.Esq)->NO.NoFolha.Chave[i] == '\0'){
                (*t)->NO.NoInterno.Dir = InsereEntre(informacao, &(*t)->NO.NoInterno.Dir, i);
            } else {
                (*t)->NO.NoInterno.Esq = InsereEntre(informacao, &(*t)->NO.NoInterno.Esq, i);
            }
        }
        return (*t);
    }
}

TipoArvore Insere (Token informacao, TipoArvore *t, Corpus *dado){
    TipoArvore p;
    if (*t == NULL){
       *t = CriaNoExt(informacao.palavra);
        return *t;
    } else {
        p = *t;

        //Analisa qual caminho seguir, se é pra esquerda ou direita, caso p seja um no interno que armazena o índice que difere e o caractere.
        while (!EExterno(p)){
            if (informacao.palavra[p->NO.NoInterno.Index] < p->NO.NoInterno.indexCaracter){ //Se o caractere for igual o nó vai ser puxado para a esquerda, para que a lógica não quebre
                p = p->NO.NoInterno.Esq;

            } else if (informacao.palavra[p->NO.NoInterno.Index] > p->NO.NoInterno.indexCaracter){
                p = p->NO.NoInterno.Dir;

            } else if (informacao.palavra[p->NO.NoInterno.Index] == p->NO.NoInterno.indexCaracter){
                if ((p->NO.NoInterno.Esq)->NO.NoFolha.Chave[p->NO.NoInterno.Index] == '\0'){
                    p = p->NO.NoInterno.Dir;
                } else {
                    p = p->NO.NoInterno.Esq;
                }
            }
        }

        int diffIndex = CompararPalavras(informacao.palavra, p->NO.NoFolha.Chave);
        
        if (diffIndex == -1){
            inserirOcorrencia(&p->NO.NoFolha.Lista, informacao.idDoc);
            return (*t);
        } else {
            (dado->v_total[(informacao.idDoc)-1])++;
            return InsereEntre(informacao, t, diffIndex);
            
        }

    }
}