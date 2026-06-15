
#define PATRICIA_c
#include <stdio.h>
#include <stdlib.h>
#include "PATRICIA.h"
#include "././loader.h"
#include "./LISTA_ENCADEADA/lista_encadeada.h"
    
    int diferenca(char *a, char*b) 
        { 
        int i = 0;
        
            while(a[i]!='/0'&& b[i]!='/0')
                {
                    if (a[i]!=b[i])
                        {
                            return i;

                        }
                    i++;    
                }
            return -1;
            
        }
    

    TipoArvore criarFolha(char *palavra)
    {
        TipoArvore p = malloc(sizeof(TipoPatNo));
        p->nt = Externo;
        strcpy(p->NO.NoFolha.Chave, palavra);
        return p;
        }
    
        
    TipoArvore criar_interno(TipoArvore *no ,int num)
        {
            
        }