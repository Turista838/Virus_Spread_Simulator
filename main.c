#include <stdio.h>
#include <stdlib.h>
#include "simulacao.h"

//Gonçalo Ramalho 2019106561

int main(int argc, char** argv) {
    
    local *dados = NULL;
    ppessoa lista = NULL;
    pitr lista_guarda = NULL;
    int contador = 0, itera = 0, controlo_itera = 0, i;
    dados = malloc (contador * sizeof(dados));
    if(dados == NULL)
        return 0;
  
    char fich[50];
    
    printf("Por favor introduza o nome do ficheiro dos espacos (.bin): ");
    scanf("%50[^\n]", fich);
    
    dados = prepara_ficheiro(fich, dados, &contador);
    if (dados == NULL)
        return 0;
    
    printf("Por favor introduza o nome do ficheiro dos pacientes (.txt): ");
    scanf(" %50[^\n]", fich);
    
    lista = prepara_lista(fich, dados, contador);
    if(lista == NULL)
        return 0;
    
    lista_guarda = cria_listas(lista_guarda, lista, itera);

    
    do {
        i = menu();
	switch(i){
            case 1: itera++;
                    controlo_itera++;
                    lista = iteracao(lista);  
                    lista_guarda = cria_listas(lista_guarda, lista, itera);
                    break; //Avança 1 iteração na simulação
            case 2: estatistica(lista, dados, contador); break; //Apresenta estatisca
            case 3: lista = adiciona_pessoa(lista, dados, contador); break; // Adiciona 1 pessoa
            case 4: lista = move_pessoa(lista, dados, contador); break; //Move N pessoas aleatoriamente
            case 5: lista = volta_atras(lista_guarda, lista, &itera, &controlo_itera); break; //Volta atrás X iterações
	}
    } while(i != 6);
    
    guarda_estatistica(lista, itera, dados, contador);

    printf("Por favor introduza o nome do ficheiro dos pacientes final (.txt): ");
    scanf(" %50[^\n]", fich);
    guarda_pacientes(lista, fich);
     
    free(dados);
    elimina_lista(lista);
    elimina_lista_de_lista(lista_guarda);
    return (EXIT_SUCCESS);
}

