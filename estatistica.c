#include <stdio.h>
#include <stdlib.h>
#include "simulacao.h"

//Gonçalo Ramalho 2019106561

void estatistica(ppessoa lista, local dados[], int cont){ //ordena por sala e por idade
    ppessoa aux = lista;
    int i, encontrou, contador_pessoas;
    float contador_doentes, contador_saudaveis, contador_imunes, total_doentes = 0,  total_saudaveis = 0, total_imunes = 0, total_pessoas = 0;

    
    for (i=0; i<cont; i++){
        encontrou = 0;
        contador_doentes = 0;
        contador_saudaveis = 0;
        contador_imunes = 0;
        contador_pessoas = 0;
        printf("########################\n");
        printf("LISTA DE PACIENTES DA SALA %d:\n", dados[i].id);
        while(lista != NULL){
            if(dados[i].id == lista->id_sl){
                encontrou = 1;
                contador_pessoas++;
                printf("%s\t%d\t%c\t", lista->nome, lista->idade, lista->estado);
                if (lista->estado != 'D')
                    printf("\n");
                if (lista->estado == 'D'){
                    printf("%d\n", lista->dias_infectado);
                    contador_doentes++;
                }
                if (lista->estado == 'S')
                    contador_saudaveis++;
                if (lista->estado == 'I')
                    contador_imunes++;
            }
            lista = lista->prox;
        }
        lista = aux;
        
        if (encontrou == 0)
            printf("SALA VAZIA!\n");
        else{
            printf("\nESTATISTICAS DA SALA %d:\n", dados[i].id);
            printf("Numero pacientes: %d\n", contador_pessoas);
            printf("Numero pacientes saudaveis: %0.f\n", contador_saudaveis);
            printf("Numero pacientes doentes: %0.f\n", contador_doentes);
            printf("Numero pacientes imunes: %0.f\n", contador_imunes);  
            printf("Taxa de saudaveis: %0.2f\n", contador_saudaveis/contador_pessoas);
            printf("Taxa de doentes: %0.2f\n", contador_doentes/contador_pessoas);
            printf("Taxa de imunes: %0.2f\n", contador_imunes/contador_pessoas);
        }
        total_doentes = total_doentes + contador_doentes;
        total_saudaveis = total_saudaveis + contador_saudaveis;
        total_imunes = total_imunes + contador_imunes;
        total_pessoas = total_pessoas + contador_pessoas;
    }
    printf("\n########################\n");
    printf("ESTATISTICAS GLOBAIS:\n");
    printf("Numero total de pacientes: %0.f\n", total_pessoas);
    printf("Numero total de pacientes saudaveis: %0.f\n", total_saudaveis);
    printf("Numero total de pacientes doentes: %0.f\n", total_doentes);
    printf("Numero total de pacientes imunes: %0.f\n", total_imunes);
    printf("Taxa total de saudaveis: %0.2f\n", total_saudaveis/total_pessoas);
    printf("Taxa total de doentes: %0.2f\n", total_doentes/total_pessoas);
    printf("Taxa total de imunes: %0.2f\n\n", total_imunes/total_pessoas);

       
}

