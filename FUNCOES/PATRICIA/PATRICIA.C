
#define PATRICIA_c
#include <stdio.h>
#include <stdlib.h>
#include "PATRICIA.h"
#include "././loader.h"
#include "./LISTA_ENCADEADA/lista_encadeada.h"
#include "string.h"
    
    int diferenca(char *a, char*b) 
        { 
        int i = 0;
        
            while(a[i]!='\0'&& b[i]!='\0')
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
    
        
TipoArvore pesquisa(char *palavra,TipoArvore arv) 
    {   TipoArvore p;
        if (arv->nt==Externo)
            {
                if(strcmp(palavra,arv->NO.NoFolha.Chave)==0)
                    {
                        
                        return arv;

                    }
                else    
                    {
                        return NULL;
                    }
            }
        if (palavra[arv->NO.NoInterno.Index] < arv->NO.NoInterno.caractere){
                    return pesquisa(palavra, arv->NO.NoInterno.Esq);
                                                                                }
        else
            return pesquisa(palavra, arv->NO.NoInterno.Dir);

        
    }

int compara_prioridade(const void *a, const void *b) {
  
    const prioridade *p1 = (const prioridade *)a;
    const prioridade *p2 = (const prioridade *)b;

   
    if (p2->valor > p1->valor) return 1;
    if (p2->valor < p1->valor) return -1;
    
    return 0; 
}

int consulta_dj(char *palavra, TipoArvore arv)
{
    TipoArvore no = pesquisa(palavra,arv);
    if (no ==NULL)
        {
            return 0;
        }
    int dj = 0;
    Celula *p = no->NO.NoFolha.Lista.primeiro;

    while (p!=NULL)
    {
        dj++;
        p = p->prox;
    }
    return dj;
}
void calcular_prioridade(TipoArvore arv,int v[],int n,char *palavra,prioridade pri[])
{
            int dj = consulta_dj(palavra, arv);

            if(dj == 0)
                return;

            double fator =log2((double)n / dj);

            for(int i = 0; i < n; i++)
            {   
                
                pri[i].valor += v[i] * fator;
                pri[i].iddoc = i;
            }
        qsort(pri, n, sizeof(prioridade), compara_prioridade);
       
        impressão(pri,n);
            
}

void impressão_relevancia(prioridade pri[],int n)
    {
        for(int i=0;i<n;i++)
            {
                if (pri!=0)
                    {
                        printf("id: %dRelevancia: %.4f\n",pri[i].iddoc,pri[i].valor);
                    }
            }
    }
void imprime_lista_ocorrencias(ListaDeIDs lista)
    {
        Celula *atual = lista.primeiro;
        while (atual!=NULL)
            {
                printf("%d, %d",atual->id.idDoc,atual->id.frequencia);
                atual=atual->prox;

            }
        }
void imprime_indice_patricia(TipoArvore arv) {
    if (arv == NULL) return;

    if (arv->nt == Interno) {
        
        imprime_indice_patricia(arv->NO.NoInterno.Esq);
        imprime_indice_patricia(arv->NO.NoInterno.Dir);
    } 

    else if (arv->nt == Externo) {
 
        printf("%s", arv->NO.NoFolha.Chave);
        
   
        imprime_lista_ocorrencias(arv->NO.NoFolha.Lista);
        
        printf("\n");
    }
}
        

    




