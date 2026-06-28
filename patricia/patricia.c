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
int CompararPalavras (char *palavra, char *palavraArvore, int *qtdComp){
    int i = 0;
    while (palavra[i] == palavraArvore[i]){

        (*qtdComp)++;
        i++;

        //Se as palavras são iguais
        if (palavra[i] == '\0' && palavraArvore[i] == '\0'){
            return -1;
        }
    } 
    return i;
}

//Algoritmo de Inserção 
TipoArvore InsereEntre (Token informacao, TipoArvore *t, int i, char caracterArv, int *qtdComp){
    TipoArvore p;
    if (EExterno(*t) || i < (*t)->NO.NoInterno.Index){

        //Quando cai aqui é duas opções, ou caiu por que é um nó externo da vez, ou seja, já está no local certinho onde a palavra nova deve ser inserida. A outra opção é quando o indice que diferiu é menor que o indice do no interno, quando acontece isso é criado um nó passando o indice novo divergente e a arvore é alocada ou no lado esquerdo ou direito, dependendo se a palavra nova é maior ou menor.
        p = CriaNoExt(informacao.palavra);

        //Inicializa a lista de ocorrencias, pois quando cai nessa função quer dizer que uma nova palavra será inserida e criará um nó na lista com seu iddoc 
        criarListaNo(&p->NO.NoFolha.Lista);
        inserirOcorrencia(&p->NO.NoFolha.Lista, informacao.idDoc);

        char caracterNovo = informacao.palavra[i];
        //Compara o caracter da nova palavra com o caracter que diferiu no nó "irmao", eu falo irmão pois na recursão a palavra nova foi até ele para comparar os caracteres e é a partir dele que olharemos se ela ficará a direita ou esquerda e qual dos caracteres que será armazenado no nó interno
        (*qtdComp)++;
        if (caracterNovo <= caracterArv){
            *t = CriaNoInt(i, &p, t, caracterNovo);
            return *t;
        } else {
            *t = CriaNoInt(i, t, &p, caracterArv);
            return *t;
        }  

    } else {
        (*qtdComp)++;
        //Percorre a arvore caso o no atual não seja externo ou caso o valor do i que difere seja maior que o armazenado no no interno da vez
        if (informacao.palavra[(*t)->NO.NoInterno.Index] <= (*t)->NO.NoInterno.indexCaracter){
            (*t)->NO.NoInterno.Esq = InsereEntre(informacao, &(*t)->NO.NoInterno.Esq, i, caracterArv, qtdComp);

        } else {
            (*t)->NO.NoInterno.Dir = InsereEntre(informacao, &(*t)->NO.NoInterno.Dir, i, caracterArv, qtdComp);
        }
        return (*t);
    }
}

TipoArvore Insere (Token informacao, TipoArvore *t, int *qtdcomparacoes){
    TipoArvore p;
    if (*t == NULL){
        (*qtdcomparacoes)++;
       *t = CriaNoExt(informacao.palavra);
       criarListaNo(&(*t)->NO.NoFolha.Lista);
       inserirOcorrencia(&(*t)->NO.NoFolha.Lista, informacao.idDoc);
        return *t;
    } else {
        p = *t;

        //Analisa qual caminho seguir, se é pra esquerda ou direita, caso p seja um no interno que armazena o índice que difere e o caractere.
        while (!EExterno(p)){
            (*qtdcomparacoes)++;
            if (informacao.palavra[p->NO.NoInterno.Index] <= p->NO.NoInterno.indexCaracter){ //Se o caractere for igual o nó vai ser puxado para a esquerda
                p = p->NO.NoInterno.Esq;

            } else {
                p = p->NO.NoInterno.Dir;

            }      
        }

        int diffIndex = CompararPalavras(informacao.palavra, p->NO.NoFolha.Chave, qtdcomparacoes);
        
        if (diffIndex == -1){
            //Caso a palavra nova já exista na arvore, irá apenas conferir de qual iddoc é ela e se já tiver na lista será incrementado 1, caso não esteja, irá criar um novo nó com seu iddoc
            inserirOcorrencia(&p->NO.NoFolha.Lista, informacao.idDoc);
            return (*t);
        } else {
            char caracterArv = p->NO.NoFolha.Chave[diffIndex]; //Armazena a letra que difere da palavra dentro da arvore para que seja comparada novamente dentro da função InsereEntre() e dite o caminho se a nova palavra vai para o no esquerdo ou direito e se o no interno armazenara ela (caso seja menor que a letra que difere da palavra nova) ou se armazenará a letra da palavra nova(caso seja menor).
            return InsereEntre(informacao, t, diffIndex, caracterArv, qtdcomparacoes);
            
        }

    }
}

//Libera memoria armazenada da arvore - chamada após o fim do programa
void liberarPatricia(TipoArvore *t){
    if (*t == NULL)return;
    if (EExterno(*t)){
        liberarLista(&(*t)->NO.NoFolha.Lista);
        free(*t);
        *t = NULL;
    } else {
        liberarPatricia(&(*t)->NO.NoInterno.Esq);
        liberarPatricia(&(*t)->NO.NoInterno.Dir);
        free(*t);
        *t = NULL;
    }
}

