#ifndef PATRICIA_H
#define PATRICIA_H
#include <stdio.h>
#include <stdlib.h>
#include "././loader.h"
#include "./LISTA_ENCADEADA/lista_encadeada.h"

#define D 8
typedef char TipoChave[MAX_PALAVRA];
typedef unsigned char TipoIndexAmp;
typedef unsigned char TipoDib;

typedef enum {
    Interno, Externo
} TipoNo;

typedef struct TipoPatNo* TipoArvore;
typedef struct TipoPatNo {
    TipoNo nt;
    union
    {
        struct {
            TipoIndexAmp Index;
            char indexCaracter;
            TipoArvore Esq, Dir;
        } NoInterno;
        struct {
            TipoChave Chave;
            ListaDeIDs Lista;
        } NoFolha;
    } NO;
    
} TipoPatNo;

#endif