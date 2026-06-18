#include "patricia.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Funções auxiliares 
short EExterno (TipoArvore p){
    return (p->nt == Externo);
}

void criarListaNo (ListaOcorrencias * lista){
    inicializarLista(&lista);
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

TipoArvore CriaNoExt (TipoChave palavra){
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

        if (palavra[i] == "\0" && palavraArvore[i] == "\0"){
            return -1;
        }
    } 
    return i;
}

//Algoritmo de Inserção 
TipoArvore InsereEntre (Token informação, TipoArvore *t, int i){
    TipoArvore p;
    if (EExterno(*t) || i < (*t)->NO.NoInterno.Index){
        p = CriaNoExt(informação.palavra);
        criarListaNo(&p->NO.NoFolha.Lista);
        inserirOcorrencia(&p->NO.NoFolha.Lista, informação.idDoc);
        
        if (i < (*t)->NO.NoInterno.Index){
            if (informação.palavra[i] < (*t)->NO.NoInterno.indexCaracter){//O if está analisando um nó que é interno
                return CriaNoInt(i, &p, t, informação.palavra[i]);
            } else {
                return CriaNoInt(i, t, &p, (*t)->NO.NoInterno.indexCaracter);
            }
        }
        if (informação.palavra[i] < (*t)->NO.NoFolha.Chave[i]){//Já aqui o if está analisando um nó que é externo
                return CriaNoInt(i, &p, t, informação.palavra[i]);
            } else {
                return CriaNoInt(i, t, &p, (*t)->NO.NoFolha.Chave[i]);
            }

    } else {
        if (informação.palavra[(*t)->NO.NoInterno.Index] <= (*t)->NO.NoInterno.indexCaracter){
            (*t)->NO.NoInterno.Esq = InsereEntre(informação, &(*t)->NO.NoInterno.Esq, i);
        } else {
            (*t)->NO.NoInterno.Dir = InsereEntre(informação, &(*t)->NO.NoInterno.Dir, i);
        }
        return (*t);
    }
}

TipoArvore Insere (Token informacao, TipoArvore *t, Corpus *dado){
    TipoArvore p;
    if (*t == NULL){
        return CriaNoExt(informacao.palavra);
    } else {
        p = *t;

        //Analisa qual caminho seguir, se é pra esquerda ou direita, caso p seja um no interno que armazena o índice que difere e o caractere.
        while (!EExterno(p)){
            if (informacao.palavra[p->NO.NoInterno.Index] <= p->NO.NoInterno.indexCaracter){ //Se o caractere for igual o nó vai ser puxado para a esquerda, para que a lógica não quebre 
                p = p->NO.NoInterno.Esq;
            } else {
                p = p->NO.NoInterno.Dir;
            }
        }

        int diffIndex = CompararPalavras(informacao.palavra, p->NO.NoFolha.Chave);
        
        if (diffIndex == -1){
            inserirOcorrencia(&p->NO.NoFolha.Lista, informacao.idDoc);
        } else {
            (dado->v_total[(informacao.idDoc)-1])++;
            return InsereEntre(informacao, t, diffIndex);
            
        }

    }
}