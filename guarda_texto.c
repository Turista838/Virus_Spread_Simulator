#include <stdio.h>
#include <stdlib.h>
#include "simulacao.h"
#define REPORT "report.txt"

//Gonçalo Ramalho 2019106561

void guarda_estatistica(ppessoa lista, int itera, local dados[], int cont){
    ppessoa aux = lista;
    int i, encontrou, contador_pessoas;
    float contador_doentes, contador_saudaveis, contador_imunes, total_doentes = 0,  total_saudaveis = 0, total_imunes = 0, total_pessoas = 0;

    
    FILE *f = fopen(REPORT, "wt");
    if (!f){
        fprintf(stderr, "Erro a criar ficheiro [10]\n");
        return;
    }
    fprintf(f, "RELATÓRIO FINAL");
    for (i=0; i<cont; i++){
        encontrou = 0;
        contador_doentes = 0;
        contador_saudaveis = 0;
        contador_imunes = 0;
        contador_pessoas = 0;
        fprintf(f, "\nLISTA DE PACIENTES DA SALA %d:\n", dados[i].id);
        while(lista != NULL){
            if(dados[i].id == lista->id_sl){
                encontrou = 1;
                contador_pessoas++;
                fprintf(f, "%s\t%d\t%c\t", lista->nome, lista->idade, lista->estado);
                if (lista->estado != 'D')
                    fprintf(f, "\n");
                if (lista->estado == 'D'){
                    fprintf(f, "%d\n", lista->dias_infectado);
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
            fprintf(f, "SALA VAZIA!\n");
        else{
            fprintf(f, "\nESTATISTICAS DA SALA %d:\n", dados[i].id);
            fprintf(f, "Numero pacientes: %d\n", contador_pessoas);
            fprintf(f, "Numero pacientes saudáveis: %0.f\n", contador_saudaveis);
            fprintf(f, "Numero pacientes doentes: %0.f\n", contador_doentes);
            fprintf(f, "Numero pacientes imunes: %0.f\n", contador_imunes);  
            fprintf(f, "Taxa de saudáveis: %0.2f\n", contador_saudaveis/contador_pessoas);
            fprintf(f, "Taxa de doentes: %0.2f\n", contador_doentes/contador_pessoas);
            fprintf(f, "Taxa de imunes: %0.2f\n", contador_imunes/contador_pessoas);
        }
        total_doentes = total_doentes + contador_doentes;
        total_saudaveis = total_saudaveis + contador_saudaveis;
        total_imunes = total_imunes + contador_imunes;
        total_pessoas = total_pessoas + contador_pessoas;
    }
    fprintf(f, "\n########################\n");
    fprintf(f, "ESTATISTICAS GLOBAIS:\n");
    fprintf(f, "Numero de iteracções: %d\n", itera);
    fprintf(f, "Numero total de pacientes: %0.f\n", total_pessoas);
    fprintf(f, "Numero total de pacientes saudáveis: %0.f\n", total_saudaveis);
    fprintf(f, "Numero total de pacientes doentes: %0.f\n", total_doentes);
    fprintf(f, "Numero total de pacientes imunes: %0.f\n", total_imunes);
    fprintf(f, "Taxa total de saudáveis: %0.2f\n", total_saudaveis/total_pessoas);
    fprintf(f, "Taxa total de doentes: %0.2f\n", total_doentes/total_pessoas);
    fprintf(f, "Taxa total de imunes: %0.2f\n\n", total_imunes/total_pessoas);
    
    fclose(f);
}
    
void guarda_pacientes(ppessoa lista, char *nomefich){
    FILE *f = fopen(nomefich, "wt");
    if (!f){
        fprintf(stderr, "Erro a criar ficheiro [10]\n");
        return;
    }
    while (lista){ 
        fprintf(f, "%s %d %c", lista->nome, lista->idade, lista->estado);
        if(lista->estado == 'D')
            fprintf(f, " %d\n", lista->dias_infectado);
        else
            fprintf(f, "\n");
        lista = lista->prox;
    }
    
    fclose(f);
}
