#include <stdio.h>
#include <stdlib.h>
#include "simulacao.h"

//Gonçalo Ramalho 2019106561

local *prepara_ficheiro(char *nomeficheiro, local *dados, int *contador){
    
    local p;
    FILE *f = fopen(nomeficheiro, "rb");
    if (f==NULL){
        fprintf(stderr, "Erro a abrir ficheiro [1] (Formato do ficheiro invalido)\n");
        return NULL;
    }

    while (fread(&p, sizeof(local),1,f) == 1)
    {
        local *verifica_espaco;
        verifica_espaco = realloc (dados, (*contador+1) * sizeof(local));
        if(verifica_espaco == NULL){
            fprintf(stderr, "Erro a reservar memoria [0]\n");
            return NULL;
        }
        dados = verifica_espaco;
        dados[*contador] = p; //Atribuição da estrutura
        (*contador)++;
    }
    fclose(f);
    
    if (verificador_dados(dados, contador)==0)
        return NULL;
    
    
    return dados;
}

int verificador_dados(local dados[], int *cont)
{
    int i, j, k, m, aux, ligam;
    for (i=0; i<*cont; i++) //verificador ID's positivos e únicos
    {
        for(j=0; j<*cont; j++)
        {
            if (i != j) // porque dados[i] é igual a dados [j] quando têm o mesmo numero
                if (dados[i].id == dados[j].id)
                {
                    fprintf(stderr, "Erro no formato do dados [3] (Locais com ID's iguais)\n");
                    return 0;
                }
        }
        if (dados[i].id < 0)
        {
            fprintf(stderr, "Erro no formato do dados [4] (ID's negativos)\n");
            return 0;
        }
    }
    
    for (i=0; i<*cont; i++) //verificador ligações correctas (separei por uma questão de legibilidade)
    {
        for (m=0; m<3;m++) //saltar liga[0-2]
        {
            ligam = 0;
            aux = dados[i].liga[m];
            for(j=0; j<*cont; j++) 
            {
                if (i != j)
                {
                    if (aux == dados[j].id) //encontrou id
                    {
                        for (k=0; k<3;k++) // verificar se liga de volta
                        {
                            if (dados[j].liga[k] == dados[i].id) 
                                ligam = 1;
                        }
                        if(ligam == 0)
                        {
                            fprintf(stderr, "Erro na formato do dados [5] (Ligacoes invalidas)\n"); // não encontrou ligação valida
                            return 0;
                        }
                    }
                }
            }
        }
    }
    return 1;
}


