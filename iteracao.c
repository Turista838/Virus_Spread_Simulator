#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "simulacao.h"
#define TAXA_DISS 0.05

//Gonçalo Ramalho 2019106561

ppessoa clonar(ppessoa lista) { //duplica a lista inicial
    ppessoa ultima = NULL, nova_lista = NULL, nova = NULL;

    while(lista!=NULL) {

        nova = (ppessoa)malloc(sizeof(pessoa));
        if(nova == NULL){
            fprintf(stderr, "Erro a reservar memoria [0]\n");
            elimina_lista(lista);
            return NULL;
        }
        *nova = *lista;
        nova->prox= NULL;
        
        if(!nova_lista)
            nova_lista = nova;
        else
            ultima->prox = nova;
        ultima = nova;
        
        
        lista=lista->prox;
    }
    return nova_lista;
}

ppessoa iteracao(ppessoa lista){
    ppessoa listafinal = NULL, aux = lista;
    
    initRandom();
    
    listafinal = clonar(lista);
    
    listafinal = duracao_maxima(listafinal); //aumenta os dias infectado, diminui os dias que faltam para a infecção passar e atribui um novo estado S/I
    
    while(lista != NULL){
        if (lista->estado == 'D'){
            listafinal = disseminacao(listafinal, lista->id_sl); //calcula quantos vai infectar e atribui o novo estado D
        }  
    lista = lista->prox;
    }
    
    lista = aux;
    
    while(lista != NULL){
        if (lista->estado == 'D'){
            listafinal = recupera(listafinal, lista->idade, lista->nome); //calcula se a pessoa recupera da infecção, e atribui um novo estado S/I
        }
        lista = lista->prox;
    }
    elimina_lista(lista);
    return listafinal;
}

ppessoa disseminacao(ppessoa lista, int id){
    ppessoa aux = lista;
    
    int nr_infectos, cont = 0, random;
    float contador = 0, taxa_di;
        
    while(aux!= NULL){ //contador de quantas novas pessoas vao adoecer
        if(id == aux->id_sl)
            contador++;
        aux = aux->prox;
    }
    
    aux = lista;
        
    taxa_di = TAXA_DISS * contador;
    nr_infectos = (int)taxa_di; //necessário para arredondar para baixo
    
    if (taxa_di < 1)
        return lista;
    
    while (cont != nr_infectos){
        while (aux!=NULL){
            random = intUniformRnd(0, 1);
            if(id == aux->id_sl){//atribuir aleatoriamente novas pessoas doentes
                if (random == 1){
                    if(aux->estado == 'S'){
                        aux->dias_infectado = 0;
                        aux->cura=(5+(aux->idade/10));
                    }
                    if(aux->estado != 'I') //só infecta se não for imune, mas fica incluido na taxa de disseminação
                        aux->estado = 'D';
                    cont++;
                }
            }
            if(cont == nr_infectos)
                break;
            aux = aux->prox;
        }
      
        aux = lista;
    }
       
    return lista;
}

ppessoa recupera(ppessoa lista, int idade, char nome[100]){
    ppessoa aux = lista;
    int p = 0;
    float a;
    a=(1.0/idade);

    p=probEvento(a);

    if (p == 1){
        while(aux!= NULL){
            if (strcmp(aux->nome, nome) == 0){
                 p=probEvento(0.2);
                 if(p == 1){
                    aux->estado = 'I';
                    aux->dias_infectado = 0;
                 }
                 else{
                    aux->estado = 'S';
                    aux->dias_infectado = 0;
                 }
            } 
        aux = aux->prox;
        }
    }

    return lista;
}

ppessoa duracao_maxima(ppessoa lista){
    ppessoa aux = lista;
    int p;

    while(aux != NULL){ //
        if(aux->estado == 'D'){
            (aux->cura)--;
            (aux->dias_infectado)++;
        }
        p=probEvento(0.2);
        if (aux->cura == 0 && aux->estado == 'D')
            if(p == 1)
                aux->estado = 'I';
            else
                aux->estado = 'S';        
        aux = aux->prox;
    }

    return lista;
}


