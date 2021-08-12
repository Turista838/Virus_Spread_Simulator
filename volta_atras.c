#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simulacao.h"

//Gonçalo Ramalho 2019106561

pitr cria_listas(pitr lista_guarda, ppessoa lista, int itera){ //cria lista de listas - histórico de iteracções
    
    pitr novo = NULL;
    ppessoa copia = NULL;

    novo = malloc(sizeof(itr));
    if(novo == NULL){ 
        fprintf(stderr, "Erro a reservar memoria [0]\n");
        return lista_guarda;
    }
    novo->r = itera;
    novo->lista_clone=NULL;
    while(lista!=NULL){
        copia = (ppessoa)malloc(sizeof(pessoa));
        if(copia == NULL){
            fprintf(stderr, "Erro a reservar memoria [0]\n");
            free(novo);
            return lista_guarda;
        }
        *copia = *lista;
        
        copia->prox = novo->lista_clone;
        novo->lista_clone = copia;
        lista=lista->prox;
    }

    novo->prox = lista_guarda;
    lista_guarda = novo;
    
    return lista_guarda;
}


ppessoa volta_atras(pitr lista_guarda, ppessoa lista, int *itera, int *controlo_itera){ //volta atrás na iteracção pretendida, max 3
    ppessoa antiga, nova = NULL;
    int a;
    
    do{//Controlador de quantas iteracções pode recuar: nunca mais de 3, e obriga a avançar iteracções para impedir recurar 2 vezes seguidas
    printf("Introduza iteracoes pretende recuar: ");
    scanf("%d", &a);
    if(a >= 1 && *controlo_itera == 0){
        printf("Tem de fazer no minimo mais uma iteracao para poder voltar atras %d vez\n", a);
        return lista;
    }
    if(a >= 2 && *controlo_itera == 1){
        printf("Tem de fazer no minimo mais uma iteracao para poder voltar atras %d vezes\n", a);
        return lista;
    }
    if(a >= 3 && *controlo_itera == 2){
        printf("Tem de fazer no minimo mais uma iteracao para poder voltar atras %d vezes\n", a);
        return lista;
    }
    if(a > *itera){
        printf("Ainda nao fez as iteracoes suficientes para poder retroceder %d vezes\n", a);
        return lista;
    }
    if (a>3 || a<=0)
        printf("So pode recuar ate 3 iteracoes\n");
    }while(a>3 || a<=0);
    
    *controlo_itera = 0; //reset controlo
    
    *itera=(*itera)-a;
    
    while(lista_guarda) {
        antiga = lista_guarda->lista_clone;
        if (lista_guarda->r == (*itera))
            nova = clonar(antiga);
        lista_guarda = lista_guarda->prox;
    }
    
    elimina_lista(lista);
   
    return nova;
    
}
