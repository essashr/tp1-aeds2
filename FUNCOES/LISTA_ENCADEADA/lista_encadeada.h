#ifndef LISTA_ENCADEADA_H
#define LISTA_ENCADEADA_H
#include "../loader.h"

typedef struct Celula* TipoApontadorLista;
typedef struct Celula {
    Token id;
    TipoApontadorLista prox;
} Celula;

typedef struct{
    Celula* primeiro;
    Celula* ultimo;
} ListaDeIDs;

void Inicializar(ListaDeIDs* lista);
void Insere(ListaDeIDs* lista, Corpus palavra);

#endif