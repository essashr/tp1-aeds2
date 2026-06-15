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

#include "patricia.h"
    
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