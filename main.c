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

void aprovarHoras() {
    for (int i = 0; i < qtdRegistros; i++) {
        if (registros[i].aprovado == 0) {
            for (int j = 0; j < qtdPessoas; j++) {
                if (pessoas[j].id == registros[i].idPessoa) {
                    printf("ID: %d\n", pessoas[j].id);
                    printf("Nome: %s\n", pessoas[j].nome);
                    printf("Horas extras: %d\n", registros[i].horasExtras);

                    printf("Insira 1 para aprovar ou 2 para negar a solicitação de horas extras pagas: ");
                    scanf("%d", &registros[i].aprovado);

                    if (registros[i].aprovado == 1) {
                        registros[i].aprovado = 1;
                        printf("Horas extras aprovadas!\n");
                    } else if (registros[i].aprovado == 2) {
                        registros[i].aprovado = 2;
                        printf("Horas extras negadas.\n");
                    } else {
                        printf("Valor inválido para avaliação de aprovação.\n");
                    }
                }
            }
        }
    }
}

void gerarRelatorio() {
    if (qtdRegistros == 0) {
        printf("Não há nenhum registro avaliado pelo gestor ou não há funcionários cadastrados.\n");
        return; // sai da função por nao ter nenhum registro
    }

    for (int i = 0; i < qtdPessoas; i++) { // 
        int totalHorasPessoa = 0; // cria essa variável de totalHoras pra cada pessoa dentro do vetor de qtdPessoas

        for (int j = 0; j < qtdRegistros; j++) {
            if (registros[j].idPessoa == pessoas[i].id && registros[j].aprovado == 1) {
                totalHorasPessoa += registros[j].horasExtras; // soma as horas aprovadas
            }
        }

        if (totalHorasPessoa > 0) { // se a pessoa tiver horas aprovadas
            printf("\nNome: %s\n", pessoas[i].nome);
            printf("ID: %d\n", pessoas[i].id);
            printf("Valor total pendente: R$%d\n", totalHorasPessoa * VALOR_HORA_EXTRA); //imprime o nome, id e o valor total pendente multiplicando pelo define do valor da hora extra
            
        }
    }
}

int main() {
    int opcao;

    do {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("1. Cadastrar funcionário\n");
        printf("2. Solicitar horas extras\n");
        printf("3. Aprovar horas extras\n");
        printf("4. Gerar relatório\n");
        printf("5. Listar pessoas\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarPessoa();
                break;
            case 2:
                solicitarHoras();
                break;
            case 3:
                aprovarHoras();
                break;
            case 4:
                gerarRelatorio();
                break;
            case 5:
                listarPessoas();
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opção não consta nas opções do sistema.Tente denovo\n");
        }

    } while (opcao != 0);

    return 0;
}
