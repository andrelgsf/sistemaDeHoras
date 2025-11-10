//1. bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//2. definições
#define MAX_PESSOAS 100
#define MAX_NOME 100
#define VALOR_HORA_EXTRA 60

//3. declarações de funções
void cadastrarPessoa();
void solicitarHoras();
void registrarHoras();
void listarPessoas();
void aprovarHoras();
void limparDados();
void gerarRelatorio();

//4. estruturas
typedef struct {
    int id;
    char nome[MAX_NOME];
} Pessoa;

typedef struct {
    int idPessoa;
    int horarioEntrada;
    int horarioSaida;
    int horasExtras;
    int aprovado; // 1 = sim, 0 = não
} RegistroHora;

//5. variáveis globais
Pessoa pessoas[MAX_PESSOAS];
int qtdPessoas = 0;

RegistroHora registros[MAX_PESSOAS];
int qtdRegistros = 0;

//6. funções
void cadastrarPessoa() {
    if (qtdPessoas >= MAX_PESSOAS) {
        printf("Limite máximo de usuários atingido.\n");
        return;
    } else {
        printf("\n-- Cadastrar funcionário --\n");
        printf("Nome do funcionário: ");
        scanf(" %[^\n]", pessoas[qtdPessoas].nome);

        printf("ID: ");
        scanf("%d", &pessoas[qtdPessoas].id);

        qtdPessoas++;

        printf("Funcionário cadastrado com sucesso.\n");
    }
}

void listarPessoas() {
    if (qtdPessoas == 0) {
        printf("Sem usuários cadastrados.\n");
    } else {
        for (int i = 0; i < qtdPessoas; i++) {
            printf("\nID: %d\n", pessoas[i].id);
            printf("Nome: %s\n", pessoas[i].nome);
        }
    }
}


void solicitarHoras() {
    if (qtdPessoas == 0) {
        printf("Não há funcionários cadastrados.\n");
        return;
    }

    listarPessoas();

    int id, entrada, saida, horasExtras;
    int encontrado = 0;

    printf("\nInsira o ID do solicitante de horas extras: ");
    scanf("%d", &id);

    for (int i = 0; i < qtdPessoas; i++) {
        if (pessoas[i].id == id) { // procura na lista de ids se o id inserido existe
            encontrado = 1;

            printf("Qual o horário de entrada (somente hora inteira): ");
            scanf("%d", &entrada);

            printf("Qual o horário de saída (somente hora inteira): ");
            scanf("%d", &saida);

            horasExtras = saida - entrada - 8;
            if (horasExtras < 0) {
                horasExtras = 0;
            }

            registros[qtdRegistros].idPessoa = id;
            registros[qtdRegistros].horarioEntrada = entrada;
            registros[qtdRegistros].horarioSaida = saida;
            registros[qtdRegistros].horasExtras = horasExtras;
            registros[qtdRegistros].aprovado = 0;
            qtdRegistros++;
            

            printf("\nFuncionário: %s\n", pessoas[i].nome);
            printf("Horas extras trabalhadas: %d\n", horasExtras);
            break;
        }
    }

    if (!encontrado) {
        printf("\nEste ID não está cadastrado na base de dados.\n");
    }
}

