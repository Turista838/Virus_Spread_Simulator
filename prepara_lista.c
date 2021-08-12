#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "simulacao.h"

//Gonçalo Ramalho 2019106561

ppessoa prepara_lista(char *ficho, local dados[], int cont){
    ppessoa listanova = NULL, novo, aux;
    pessoa p;
    
    int i, k, j, x = 0, y, controlador, falta, random;
    char sai = 'N';

    initRandom();
    
    for(i=0; i<cont; i++) // descobrir qual o ID maior
    {
        if (dados[i].id > x )
            x = dados[i].id;
    }
    y = x;
    for(i=0; i<cont; i++) // descobrir qual o ID menor
    {
        if (y > dados[i].id)
            y = dados[i].id;
    }
    
    FILE *f = fopen(ficho,"rt"); //vai abrir o ficheiro de texto para leitura
    if (!f){
        fprintf(stderr, "Erro a abrir ficheiro [2] (Formato do ficheiro invalido)\n");
        return listanova;
    }
    
    p.prox = NULL;
    
    while (fscanf(f," %s %d %c", p.nome, &p.idade, &p.estado) == 3 && sai != 'S') { //leitor do ficheiro de texto
       
       if (p.estado == 'S' || p.estado == 'I' || p.estado == 'D') { //verificador de estado
            if (p.estado=='D') { //atribuidor de quantos dias para cura se doente
                p.cura=(5+(p.idade/10));
                fscanf(f,"%d", &p.dias_infectado);
                if (p.dias_infectado < 0) { //verificador dias infectado
                    fprintf(stderr,"Erro no formato da lista [9] (Dias infectado invalido)\n");
                    elimina_lista(listanova);
                    fclose(f);
                    return NULL;
                }    
            }    
        }
        else {
                fprintf(stderr,"Erro no formato da lista [8] (Estado invalido)\n");
                elimina_lista(listanova);
                fclose(f);
                return NULL;
        }
        if (p.idade < 0) { //verificador de idade
            fprintf(stderr,"Erro no formato da lista [7] (Idade invalida)\n");
            elimina_lista(listanova);
            fclose(f);
            return NULL;
        }
        aux = listanova;
        while(aux) { //verificador de nomes iguais        
            if (strcmp(aux->nome, p.nome) == 0){
                fprintf(stderr,"Erro no formato da lista [6] (Nomes duplicados)\n");
                elimina_lista(listanova);
                fclose(f);
                return NULL;
            }
            aux = aux->prox;
        }
        
        novo = malloc(sizeof(pessoa));
        if(novo == NULL){
            fprintf(stderr, "Erro a reservar memoria [0]\n");
            elimina_lista(listanova);
            fclose(f);
            return NULL;
        }
        
        controlador = 0;
        while (!controlador) //ciclo para atribuição de salas
        {
        random = intUniformRnd(y, x);

        falta = 0;
        
            for (j=0; j<cont; j++)
            {
                if (random == dados[j].id  && dados[j].capacidade > 0) { //encontra uma sala disponovel, atribuí e sai
                    p.id_sl = random;
                    (dados[j].capacidade)--;
                    *novo = p;
                    controlador = 1;
                }
                if (random == dados[j].id  && dados[j].capacidade == 0){ // quando encontra uma sala vazia, sai e não atribuí
                    for (k=0; k<cont; k++){
                        falta = dados[k].capacidade + falta;
                    }
                    if (falta == 0){
                        controlador = 1;
                        sai= 'S';
                        printf("AVISO: Salas atingiram o limite\n");
                    }
                }
            }
        }
        
        novo->prox = listanova;
        listanova = novo;
        
    }
    
    fclose(f);
    return listanova;
}
    