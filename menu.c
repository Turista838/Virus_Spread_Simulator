#include <stdio.h>
#include <stdlib.h>
#include "simulacao.h"

//Gonçalo Ramalho 2019106561

int menu(){
	int i;
	
	puts("1 - Avancar 1 Iteracao na Simulacao");
	puts("2 - Apresentar Estatistica");
	puts("3 - Adicionar Doente");
	puts("4 - Transferir Pacientes");
        puts("5 - Retroceder X Iteracoes");
	puts("6 - Terminar Simulacao");
	puts("Escolha uma opcao: ");
	
	do{
            scanf("%d", &i);
	}while(i<1 || i>6);
	return i;	
}
