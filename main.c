#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PESSOAS 100
#define MAX_NOME 100
#define VALOR_HORA_EXTRA 60

// ----------------------
//  ESTRUTURAS
// ----------------------
typedef struct {
    int id;
    char nome[MAX_NOME];
} Pessoa;

typedef struct {
    int idPessoa;
    int horarioEntrada;
    int horarioSaida;
    int horasExtras;
    int aprovado; // 1 = aprovado, 2 = negado, 0 = pendente
} RegistroHora;

// ----------------------
//  VARIÁVEIS GLOBAIS
// ----------------------
Pessoa pessoas[MAX_PESSOAS];
int qtdPessoas = 0;

RegistroHora registros[MAX_PESSOAS];
int qtdRegistros = 0;

// ----------------------
//  FUNÇÕES DE ARQUIVOS
// ----------------------
void salvarPessoas() {
    FILE *f = fopen("pessoas.dat", "wb");
    if (!f) {
        printf("Erro ao salvar pessoas.\n");
        return;
    }

    fwrite(&qtdPessoas, sizeof(int), 1, f);
    fwrite(pessoas, sizeof(Pessoa), qtdPessoas, f);

    fclose(f);
}

void carregarPessoas() {
    FILE *f = fopen("pessoas.dat", "rb");
    if (!f) return;

    fread(&qtdPessoas, sizeof(int), 1, f);
    fread(pessoas, sizeof(Pessoa), qtdPessoas, f);

    fclose(f);
}

void salvarRegistros() {
    FILE *f = fopen("registros.dat", "wb");
    if (!f) {
        printf("Erro ao salvar registros.\n");
        return;
    }

    fwrite(&qtdRegistros, sizeof(int), 1, f);
    fwrite(registros, sizeof(RegistroHora), qtdRegistros, f);

    fclose(f);
}

void carregarRegistros() {
    FILE *f = fopen("registros.dat", "rb");
    if (!f) return;

    fread(&qtdRegistros, sizeof(int), 1, f);
    fread(registros, sizeof(RegistroHora), qtdRegistros, f);

    fclose(f);
}

// ----------------------
//  FUNÇÕES DO SISTEMA
// ----------------------
void cadastrarPessoa() {
    if (qtdPessoas >= MAX_PESSOAS) {
        printf("Limite máximo de usuários atingido.\n");
        return;
    }

    printf("\n-- Cadastrar funcionário --\n");
    printf("Nome do funcionário: ");
    scanf(" %[^\n]", pessoas[qtdPessoas].nome);

    printf("ID: ");
    scanf("%d", &pessoas[qtdPessoas].id);

    qtdPessoas++;

    salvarPessoas();

    printf("Funcionário cadastrado com sucesso.\n");
}


void listarPessoas() {
    if (qtdPessoas == 0) {
        printf("Sem usuários cadastrados.\n");
        return;
    }

    for (int i = 0; i < qtdPessoas; i++) {
        printf("\nID: %d\n", pessoas[i].id);
        printf("Nome: %s\n", pessoas[i].nome);
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
        if (pessoas[i].id == id) {
            encontrado = 1;

            printf("Horário de entrada (somente hora): ");
            scanf("%d", &entrada);

            printf("Horário de saída (somente hora): ");
            scanf("%d", &saida);

            horasExtras = saida - entrada - 8;
            if (horasExtras < 0) horasExtras = 0;

            registros[qtdRegistros].idPessoa = id;
            registros[qtdRegistros].horarioEntrada = entrada;
            registros[qtdRegistros].horarioSaida = saida;
            registros[qtdRegistros].horasExtras = horasExtras;
            registros[qtdRegistros].aprovado = 0; // pendente
            qtdRegistros++;

            salvarRegistros();

            printf("\nFuncionário: %s\n", pessoas[i].nome);
            printf("Horas extras solicitadas: %d\n", horasExtras);
            break;
        }
    }

    if (!encontrado) {
        printf("ID não encontrado.\n");
    }
}


void aprovarHoras() {
    for (int i = 0; i < qtdRegistros; i++) {
        if (registros[i].aprovado == 0) { // só pendentes
            for (int j = 0; j < qtdPessoas; j++) {
                if (pessoas[j].id == registros[i].idPessoa) {

                    printf("\nID: %d\n", pessoas[j].id);
                    printf("Nome: %s\n", pessoas[j].nome);
                    printf("Horas extras: %d\n", registros[i].horasExtras);

                    printf("1 = aprovar | 2 = negar: ");
                    scanf("%d", &registros[i].aprovado);

                    if (registros[i].aprovado == 1) {
                        printf("Horas extras aprovadas.\n");
                    } else if (registros[i].aprovado == 2) {
                        printf("Horas extras negadas.\n");
                    } else {
                        printf("Opção inválida.\n");
                        registros[i].aprovado = 0;
                    }

                    salvarRegistros();
                }
            }
        }
    }
}

void gerarRelatorio() {
    if (qtdRegistros == 0) {
        printf("Nenhum registro encontrado.\n");
        return;
    }

    for (int i = 0; i < qtdPessoas; i++) {
        int totalHoras = 0;

        for (int j = 0; j < qtdRegistros; j++) {
            if (registros[j].idPessoa == pessoas[i].id && registros[j].aprovado == 1) {
                totalHoras += registros[j].horasExtras;
            }
        }

        if (totalHoras > 0) {
            printf("\nNome: %s\n", pessoas[i].nome);
            printf("ID: %d\n", pessoas[i].id);
            printf("Valor total a receber: R$ %d\n", totalHoras * VALOR_HORA_EXTRA);
        }
    }
}

// ----------------------
//        MAIN
// ----------------------
int main() {
    int opcao;

    // Carregar dados ao iniciar
    carregarPessoas();
    carregarRegistros();

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
            case 1: cadastrarPessoa(); break;
            case 2: solicitarHoras(); break;
            case 3: aprovarHoras(); break;
            case 4: gerarRelatorio(); break;
            case 5: listarPessoas(); break;
            case 0: printf("Saindo do sistema...\n"); break;
            default: printf("Opção inválida.\n");
        }

    } while (opcao != 0);

    return 0;
}
