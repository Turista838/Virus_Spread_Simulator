#ifndef SIMULACAO_H
#define SIMULACAO_H

//Gonçalo Ramalho 2019106561

typedef struct sala local, *plocal;
struct sala{ //SALAS
    int id; // id numérico do local
    int capacidade; // capacidade máxima
    int liga[3]; // id das ligações (-1 nos casos não usados)
};

typedef struct lista pessoa, *ppessoa;
struct lista{ //PESSOAS
    int id_sl; //id numérico do local que foi atribuido à pessoa
    char nome[100]; //nome da pessoa
    int idade; //idade da pessoa
    char estado; //estado em que a pessoa se encontra
    int dias_infectado; // há quantos dias está infectado
    int cura; //dias para a infecção passar
    ppessoa prox;
};

typedef struct nr_itera itr, *pitr;
struct nr_itera{ //LISTA DE LISTA DE PESSOAS
    int r; //id numérico da iteracção introduzida
    ppessoa lista_clone;
    pitr prox;
};

void initRandom();
int intUniformRnd(int a, int b);
int probEvento(float prob);
void elimina_lista(ppessoa lista);
void elimina_lista_de_lista(pitr lista_guarda);

int menu();

local *prepara_ficheiro(char *nomeficheiro, local *dados, int *contador);
int verificador_dados(local dados[], int *cont);

ppessoa prepara_lista(char *ficho, local dados[], int cont);

ppessoa clonar(ppessoa lista);
ppessoa iteracao(ppessoa lista);
ppessoa disseminacao(ppessoa lista, int id);
ppessoa recupera(ppessoa lista, int idade, char nome[100]);
ppessoa duracao_maxima(ppessoa lista);

void estatistica(ppessoa lista, local dados[], int cont);

ppessoa procuraPessoa(ppessoa lista, char nome[100]);
ppessoa adiciona_pessoa(ppessoa lista, local dados[], int cont);
ppessoa move_pessoa (ppessoa lista, local dados[], int cont);

void guarda_pacientes(ppessoa lista, char *nomefich);
void guarda_estatistica(ppessoa lista, int itera, local dados[], int cont);

ppessoa volta_atras(pitr lista_guarda, ppessoa lista, int *itera, int *controlo_itera);
pitr cria_listas(pitr lista_guarda, ppessoa lista, int itera);


#endif
