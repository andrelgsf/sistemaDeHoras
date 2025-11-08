
//1.bibliotecas

#include <stdio.h>   
#include <stdlib.h> 
#include <string.h>  
#include <time.h> 

//2.definições

#define MAX_PESSOAS 100
#define MAX_NOME 100
#define VALOR_HORA_EXTRA 60

//3.declarações de funções

void cadastrarPessoa();
void solicitarHoras();
void registrarHoras();
void listarPessoas();
void aprovarHoras();
void limparDados();
void gerarRelatorio();

// 4.estruturas

typedef struct
{
  int id;
  char nome[MAX_NOME];
}  Pessoa;

typedef struct 
{
  int idPessoa;
  int horarioEntrada;
  int horarioSaida;
  int horasExtras;
  int aprovado; // 1 = sim, 0 = não
} RegistroHora;

// 5.variaveis

Pessoa pessoas [MAX_PESSOAS];
int qtdPessoas = 0;

// 6.funções

void cadastrarPessoa(){
    if(qtdPessoas >= MAX_PESSOAS){
        printf("Limite máximo de usários atingido. \n");
        return;

       } else {

            printf("\n --Cadastrar funcionário--\n");
            printf("Nome do funcionário: ");
            scanf(" %[^\n]", pessoas[qtdPessoas].nome);
            getchar();

            printf("ID: ");
            scanf("%d", &pessoas[qtdPessoas].id);
            getchar();

            qtdPessoas++;

             printf("Funcionário cadastrado com sucesso. \n");
        }
    
}
