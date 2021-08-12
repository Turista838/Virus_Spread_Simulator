#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simulacao.h"

//Gonçalo Ramalho 2019106561

ppessoa procuraPessoa(ppessoa lista, char nome[100]) {
    ppessoa aux = lista;
    while(aux) {
        if (strcmp(aux->nome, nome) == 0)
            return aux;
        aux = aux->prox;
    }
    return NULL;
}

ppessoa adiciona_pessoa (ppessoa lista, local dados[], int cont){
    pessoa p;
    ppessoa nova, aux;
    int i, encontrei = 0;
    
    printf("Introduza o numero da sala: ");
    scanf("%d", &p.id_sl);
    for(i=0; i<cont; i++){
        if(p.id_sl == dados[i].id){
            encontrei = 1;
            if(dados[i].capacidade == 0){
                printf("Sala cheia!\n");
                return lista;
            }
            (dados[i].capacidade)--;
        }           
    }
    if (encontrei == 0){
        printf("Sala nao encontrada!\n");
        return lista;
    }
    
    printf("Introduza o nome: ");
    scanf(" %99[^\n]", p.nome);
    
    if(procuraPessoa(lista, p.nome) != NULL){
        printf("Erro: ja existe paciente com o mesmo nome\n");
        return lista;
    }
    
    do{
        printf("Introduza a idade: ");
        scanf(" %d", &p.idade);
        if(p.idade <= 0)
            printf("Idade tem de ser maior ou igual a 0\n");
    }while(p.idade <= 0);
    
    printf("Introduza o estado: ");
    scanf(" %c", &p.estado);
    if(p.estado != 'D' && p.estado != 'S' && p.estado != 'I'){
        printf("Estado invalido\n"); 
        return lista;
    }

    if(p.estado == 'D'){
        do{
            printf("Introduza ha quantos dias esta doente: ");
            scanf(" %d", &p.dias_infectado);
            p.cura=(5+(p.idade/10));
        }while(p.dias_infectado < 0);
    }
 
    nova = malloc(sizeof(pessoa));
    if (nova == NULL){
        fprintf(stderr, "Erro a reservar memoria [0]\n");
        return lista;
    }
    
    *nova = p;
    nova->prox = NULL;
    
    if(lista == NULL)
        lista = nova;
    else {
        aux = lista;
        while(aux->prox != NULL){
            
            aux = aux->prox;
        }
        aux->prox = nova;
    }
    
    return lista;
}

ppessoa move_pessoa (ppessoa lista, local dados[], int cont){
    ppessoa aux = lista;
    int i, j, random = 0, ligam = 0, primeira, segunda, mov_p, encontrei_p = 0, encontrei_s = 0, contador_pessoas = 0;
    
    printf("Quantas pessoas pretende mover: ");
    do{
    scanf("%d", &mov_p);
    }while(mov_p <= 0);
    printf("Da sala: ");
    scanf("%d", &primeira);
    printf("Para a sala: ");
    scanf("%d", &segunda);
    
    for (i=0; i<cont; i++){ //verifica se existe sala e e existem pessoas suficientes
        if(dados[i].id == primeira){
            encontrei_p = 1;
            while(lista != NULL){
                if(lista->id_sl == primeira){
                    contador_pessoas++; //conta as pessoas disponiveis na sala
                }
                lista = lista->prox;
            }
            lista = aux;
        }
        if(dados[i].id == segunda)
            encontrei_s = 1;
    } 
    
    if( (encontrei_p + encontrei_s) == 0){
        printf("A salas nao existem\n");
        return lista;
    }
    if(encontrei_p == 1 && encontrei_s == 0){
        printf("A segunda sala nao existe\n");
        return lista;
    }
    if(encontrei_p == 0 && encontrei_s == 1){
        printf("A primeira sala nao existe\n");
        return lista;
    }
    
    if(mov_p > contador_pessoas){
        printf("Nao existem %d pessoas na sala %d para mover\n", mov_p, primeira);
        return lista;
    }
    
    for(i=0; i<cont; i++){ //verificador de ligação de ida
        if(dados[i].id == primeira){
            for(j=0; j<3; j++){
                if (dados[i].liga[j] == segunda)
                    ligam = 1;     
            }
        }
    }
    
    if(ligam == 0){
        printf("As salas nao possuem ligacao entre si\n");
        return lista;
    }
    
    for(i=0; i<cont; i++){ //verificador de ligação de volta
        if(dados[i].id == segunda){
            for(j=0; j<3; j++){
                if (dados[i].liga[j] == primeira)
                    ligam = 2;
            }
        }
    }
    
    if(ligam == 1){
        printf("As salas nao possuem ligacao entre si\n");
        return lista;
    }
    
    for(i=0; i<cont; i++){//aumenta e diminui a capacidade das salas
        if(dados[i].id == primeira)
           dados[i].capacidade = dados[i].capacidade + mov_p; 
        if(dados[i].id == segunda){
            if(dados[i].capacidade >= mov_p)
                dados[i].capacidade = dados[i].capacidade - mov_p; 
            else{
                printf("A segunda sala nao tem capacidade suficiente\n");
                return lista;
            }
        }      
    }
    
    initRandom();
    
    while(mov_p !=0){//atribuir aleatoriamente os pacientes às salas
        while(lista != NULL){
            if(lista->id_sl == primeira){
                random = intUniformRnd(0, 1);
                if(random == 1){
                    lista->id_sl = segunda;
                    mov_p--;
                }
            }
            lista = lista->prox;
            if(mov_p == 0)
                break;
        }
        lista = aux;
    }
    
    return lista;
         
}