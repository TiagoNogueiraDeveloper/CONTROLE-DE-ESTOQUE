#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "estruturas.h"

// Define o limite máximo de clientes que o sistema pode armazenar.
#define TAM_CLIENTES 100

// Função para limpar o buffer de entrada do teclado.
void limparBufferClientes()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
        // Consome os caracteres restantes até o fim da linha.
    }
}

// Função para remover caracteres não numéricos do CPF digitado.
void limparCpf(const char *entrada, char *saida)
{
    int j = 0;

    for (int i = 0; entrada[i] != '\0'; i++)
    {
        if (entrada[i] >= '0' && entrada[i] <= '9')
        {
            saida[j] = entrada[i];
            j++;
        }
    }

    saida[j] = '\0';
}

// Função para validar se o CPF é válido de acordo com a regra oficial.
int validarCPF(const char *cpf)
{
    int digitos[11];
    int soma = 0;
    int resto;
    int digito1;
    int digito2;

    // O CPF deve ter exatamente 11 dígitos.
    if (strlen(cpf) != 11)
    {
        return 0;
    }

    // Verifica se todos os caracteres são números.
    for (int i = 0; i < 11; i++)
    {
        if (!isdigit((unsigned char)cpf[i]))
        {
            return 0;
        }

        digitos[i] = cpf[i] - '0';
    }

    // Cálculo do primeiro dígito verificador.
    for (int i = 0; i < 9; i++)
    {
        soma += digitos[i] * (10 - i);
    }

    resto = soma % 11;
    digito1 = (resto < 2) ? 0 : 11 - resto;

    // Cálculo do segundo dígito verificador.
    soma = 0;
    for (int i = 0; i < 10; i++)
    {
        soma += digitos[i] * (11 - i);
    }

    resto = soma % 11;
    digito2 = (resto < 2) ? 0 : 11 - resto;

    // Compara os dígitos calculados com os dígitos informados.
    if (digitos[9] != digito1 || digitos[10] != digito2)
    {
        return 0;
    }

    // Evita CPFs compostos por todos os dígitos iguais, que são inválidos.
    for (int i = 1; i < 11; i++)
    {
        if (digitos[i] != digitos[0])
        {
            return 1;
        }
    }

    return 0;
}

// Verifica se já existe um cliente cadastrado com o mesmo CPF.
int cpfJaCadastrado(struct Cliente clientes[], int qtdClientes, const char *cpf)
{
    for (int i = 0; i < qtdClientes; i++)
    {
        if (strcmp(clientes[i].cpf, cpf) == 0)
        {
            return 1;
        }
    }

    return 0;
}

// Cadastra um novo cliente no sistema.
void incluirCliente(struct Cliente clientes[], int *qtdClientes)
{
    char nome[50];
    char cpfEntrada[15];
    char cpf[12];
    int i;

    // Impede cadastro quando o limite de clientes for atingido.
    if (*qtdClientes >= TAM_CLIENTES)
    {
        printf("\nLimite de clientes atingido!\n");
        return;
    }

    // Limpa o buffer antes de ler strings.
    limparBufferClientes();

    // Solicita o nome completo do cliente.
    printf("\nDigite o nome completo do cliente: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    // Valida se o nome não ficou em branco.
    int nomeValido = 0;
    for (int j = 0; nome[j] != '\0'; j++)
    {
        if (!isspace((unsigned char)nome[j]))
        {
            nomeValido = 1;
            break;
        }
    }

    if (!nomeValido)
    {
        printf("\nO nome nao pode ficar em branco!\n");
        return;
    }

    // Solicita e limpa o CPF informado.
    printf("Digite o CPF: ");
    fgets(cpfEntrada, sizeof(cpfEntrada), stdin);
    cpfEntrada[strcspn(cpfEntrada, "\n")] = '\0';

    limparCpf(cpfEntrada, cpf);

    // Valida o CPF digitado.
    if (!validarCPF(cpf))
    {
        printf("\nCPF invalido!\n");
        return;
    }

    // Evita cadastro de CPF duplicado.
    if (cpfJaCadastrado(clientes, *qtdClientes, cpf))
    {
        printf("\nCPF ja cadastrado no sistema!\n");
        return;
    }

    // Armazena os dados do cliente na próxima posição disponível.
    i = *qtdClientes;
    clientes[i].id = i + 1;
    strcpy(clientes[i].nome, nome);
    strcpy(clientes[i].cpf, cpf);
    clientes[i].totalVendas = 0;

    (*qtdClientes)++;

    printf("\nCliente cadastrado com sucesso!\n");
}

// Remove um cliente pelo ID informado.
void excluirCliente(struct Cliente clientes[], int *qtdClientes)
{
    int idExcluir;

    // Verifica se existe algum cliente cadastrado.
    if (*qtdClientes == 0)
    {
        printf("\nNenhum cliente cadastrado!\n");
        return;
    }

    // Solicita o ID do cliente a ser removido.
    printf("\nDigite o ID do cliente: ");
    scanf("%d", &idExcluir);

    // Procura o cliente pelo ID e remove da lista.
    for (int i = 0; i < *qtdClientes; i++)
    {
        if (clientes[i].id == idExcluir)
        {
            for (int j = i; j < *qtdClientes - 1; j++)
            {
                clientes[j] = clientes[j + 1];
            }

            (*qtdClientes)--;
            printf("\nCliente removido com sucesso!\n");
            return;
        }
    }

    printf("\nCliente nao encontrado!\n");
}

// Lista todos os clientes cadastrados.
void listarClientes(struct Cliente clientes[], int qtdClientes)
{
    if (qtdClientes == 0)
    {
        printf("\nNenhum cliente cadastrado!\n");
        return;
    }

    printf("\n========= LISTA DE CLIENTES =========\n");

    for (int i = 0; i < qtdClientes; i++)
    {
        printf("\nID: %d\n", clientes[i].id);
        printf("CPF: %s\n", clientes[i].cpf);
        printf("Nome: %s\n", clientes[i].nome);
        printf("Total de vendas: %d\n", clientes[i].totalVendas);
    }
}

// Salva a lista de clientes em um arquivo binário.
void salvarClientes(struct Cliente clientes[], int qtdClientes)
{
    FILE *arquivo = fopen("clientes.dat", "wb");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir arquivo de clientes!\n");
        return;
    }

    fwrite(&qtdClientes, sizeof(int), 1, arquivo);
    fwrite(clientes, sizeof(struct Cliente), qtdClientes, arquivo);

    fclose(arquivo);
}

// Carrega a lista de clientes a partir de um arquivo binário.
void carregarClientes(struct Cliente clientes[], int *qtdClientes)
{
    FILE *arquivo = fopen("clientes.dat", "rb");

    if (arquivo == NULL)
    {
        *qtdClientes = 0;
        return;
    }

    fread(qtdClientes, sizeof(int), 1, arquivo);
    fread(clientes, sizeof(struct Cliente), *qtdClientes, arquivo);

    fclose(arquivo);
}