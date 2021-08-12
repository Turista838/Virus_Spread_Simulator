#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "simulacao.h"

//Gonçalo Ramalho 2019106561

void initRandom(){
    srand(time(NULL));
}

int intUniformRnd(int a, int b){
    return a + rand()%(b-a+1);
}

int probEvento(float prob){
    return prob > ((float)rand()/RAND_MAX);
}

void elimina_lista(ppessoa lista){
    ppessoa aux;
    while (lista){
        aux = lista;
        lista = lista->prox;
        free(lista);
    }
}

void elimina_lista_de_lista(pitr lista_guarda){
    pitr aux;

    while(lista_guarda != NULL){
        elimina_lista(lista_guarda->lista_clone);
        aux = lista_guarda;
        lista_guarda = lista_guarda->prox;
        free(aux);
    }
}




