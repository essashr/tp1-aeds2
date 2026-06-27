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
TipoArvore InsereEntre (Token informacao, TipoArvore *t, int i, char caracterArv){
    TipoArvore p;
    if (EExterno(*t) || i < (*t)->NO.NoInterno.Index){
        p = CriaNoExt(informacao.palavra);

        //Inicializa a lista de ocorrencias, pois quando cai nessa função quer dizer que uma nova palavra será inserida e criará um nó na lista com seu iddoc 
        criarListaNo(&p->NO.NoFolha.Lista);
        inserirOcorrencia(&p->NO.NoFolha.Lista, informacao.idDoc);

        char caracterNovo = informacao.palavra[i];
        //Compara o caracter da nova palavra com o caracter que diferiu no nó "irmao", eu falo irmão pois na recursão a palavra nova foi até ele para comparar os caracteres e é a partir dele que olharemos se ela ficará a direita ou esquerda e qual dos caracteres que será armazenado no nó interno
        if (caracterNovo <= caracterArv){
            *t = CriaNoInt(i, &p, t, caracterNovo);
            return *t;
        } else {
            *t = CriaNoInt(i, t, &p, caracterArv);
            return *t;
        }  

    } else {
        if (informacao.palavra[(*t)->NO.NoInterno.Index] <= (*t)->NO.NoInterno.indexCaracter){
            (*t)->NO.NoInterno.Esq = InsereEntre(informacao, &(*t)->NO.NoInterno.Esq, i, caracterArv);

        } else {
            (*t)->NO.NoInterno.Dir = InsereEntre(informacao, &(*t)->NO.NoInterno.Dir, i, caracterArv);
        }
        return (*t);
    }
}

TipoArvore Insere (Token informacao, TipoArvore *t, Corpus *dado){
    TipoArvore p;
    if (*t == NULL){
       *t = CriaNoExt(informacao.palavra);
       criarListaNo(&(*t)->NO.NoFolha.Lista);
       inserirOcorrencia(&(*t)->NO.NoFolha.Lista, informacao.idDoc);
        return *t;
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
            //Caso a palavra nova já exista na arvore, irá apenas conferir de qual iddoc é ela e se já tiver na lista será incrementado 1, caso não esteja, irá criar um novo nó com seu iddoc
            inserirOcorrencia(&p->NO.NoFolha.Lista, informacao.idDoc);
            return (*t);
        } else {
            //(dado->v_total[(informacao.idDoc)-1])++;
            char caracterArv = p->NO.NoFolha.Chave[diffIndex];
            return InsereEntre(informacao, t, diffIndex, caracterArv);
            
        }

    }
}

TipoArvore pesquisa(char *palavra, TipoArvore arv){
    TipoArvore p;
    if (arv->nt == Externo){
        if (strcmp(palavra, arv->NO.NoFolha.Chave) == 0){
            return arv;
        }else{
            return NULL;
        }
    }
    if (palavra[arv->NO.NoInterno.Index] < arv->NO.NoInterno.indexCaracter){
        return pesquisa(palavra, arv->NO.NoInterno.Esq);
    }else{
        return pesquisa(palavra, arv->NO.NoInterno.Dir);
    }
}

int diferenca(char *a, char *b){
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0'){
        if (a[i] != b[i])
            return i;
        i++;
    }
    return -1;
}
