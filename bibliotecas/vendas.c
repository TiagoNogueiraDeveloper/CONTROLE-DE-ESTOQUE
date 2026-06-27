#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "estruturas.h"

#define TAM_VENDAS 100

// Função para limpar o buffer de entrada do teclado.
// Isso evita que caracteres residuais atrapalhem a leitura das próximas entradas.
void limparBufferVendas()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
        // Consome os caracteres restantes até encontrar o fim da linha.
    }
}

// Função que verifica se um ano é bissexto.
// Ela é usada para validar datas como 29/02/2024.
int anoBissexto(int ano)
{
    if ((ano % 400 == 0) || (ano % 4 == 0 && ano % 100 != 0))
    {
        return 1;
    }

    return 0;
}

// Função que valida uma data no formato dd/mm/aaaa.
// Retorna 1 quando a data é válida e 0 quando não é.
int validarData(const char *data)
{
    int dia, mes, ano;
    int qtdCaracteres;

    // A data deve ter exatamente 10 caracteres: dd/mm/aaaa.
    if (strlen(data) != 10)
    {
        return 0;
    }

    // Os separadores devem estar nas posições corretas.
    if (data[2] != '/' || data[5] != '/')
    {
        return 0;
    }

    // Converte a string para números inteiros.
    qtdCaracteres = sscanf(data, "%d/%d/%d", &dia, &mes, &ano);
    if (qtdCaracteres != 3)
    {
        return 0;
    }

    // Valida faixa básica de ano, mês e dia.
    if (ano < 1 || mes < 1 || mes > 12 || dia < 1)
    {
        return 0;
    }

    // Trata anos bissextos para fevereiro.
    if (mes == 2)
    {
        if (anoBissexto(ano))
        {
            return dia <= 29;
        }
        return dia <= 28;
    }

    // Meses com 30 dias.
    if (mes == 4 || mes == 6 || mes == 9 || mes == 11)
    {
        return dia <= 30;
    }

    // Meses com 31 dias.
    return dia <= 31;
}

// Busca um cliente no vetor pelo CPF informado.
// Se encontrar, retorna o índice do cliente; caso contrário, retorna -1.
int buscarClientePorCPF(struct Cliente clientes[], int qtdClientes, const char *cpf)
{
    for (int i = 0; i < qtdClientes; i++)
    {
        if (strcmp(clientes[i].cpf, cpf) == 0)
        {
            return i;
        }
    }

    return -1;
}

// Busca um produto no vetor pelo ID informado.
// Se encontrar, retorna o índice do produto; caso contrário, retorna -1.
int buscarProdutoPorID(struct Produtos produtos[], int qtdProdutos, int idProduto)
{
    for (int i = 0; i < qtdProdutos; i++)
    {
        if (produtos[i].id == idProduto)
        {
            return i;
        }
    }

    return -1;
}

// Função principal para registrar uma nova venda.
// Ela valida a data, verifica se o cliente e o produto existem e confirma se há estoque suficiente.
int incluirVenda(struct Venda vendas[], int *qtdVendas, struct Cliente clientes[], int qtdClientes, struct Produtos produtos[], int qtdProdutos)
{
    char data[11];
    char cpfEntrada[15];
    char cpf[12];
    int idProduto;
    int quantidade;
    int indiceCliente;
    int indiceProduto;

    // Impede que sejam cadastradas mais vendas do que o limite definido.
    if (*qtdVendas >= TAM_VENDAS)
    {
        printf("\nLimite de vendas atingido!\n");
        return 0;
    }

    // Limpa o buffer antes de ler os dados seguintes.
    limparBufferVendas();

    // Solicita e lê a data da venda.
    printf("\nDigite a data da venda (dd/mm/aaaa): ");
    fgets(data, sizeof(data), stdin);
    data[strcspn(data, "\n")] = '\0';

    // Valida se a data informada é real.
    if (!validarData(data))
    {
        printf("\nData invalida!\n");
        return 0;
    }

    // Solicita o CPF do cliente.
    printf("Digite o CPF do cliente: ");
    limparBufferVendas();
    fgets(cpfEntrada, sizeof(cpfEntrada), stdin);
    cpfEntrada[strcspn(cpfEntrada, "\n")] = '\0';

    // Remove caracteres não numéricos para padronizar o CPF.
    limparCpf(cpfEntrada, cpf);

    // Verifica se o cliente está cadastrado.
    indiceCliente = buscarClientePorCPF(clientes, qtdClientes, cpf);
    if (indiceCliente == -1)
    {
        printf("\nCPF nao cadastrado no sistema!\n");
        return 0;
    }

    // Solicita o ID do produto vendido.
    printf("Digite o ID do produto: ");
    scanf("%d", &idProduto);

    // Verifica se o produto existe.
    indiceProduto = buscarProdutoPorID(produtos, qtdProdutos, idProduto);
    if (indiceProduto == -1)
    {
        printf("\nProduto nao encontrado!\n");
        return 0;
    }

    // Solicita a quantidade vendida.
    printf("Digite a quantidade vendida: ");
    scanf("%d", &quantidade);

    // Evita quantidades inválidas ou negativas.
    if (quantidade <= 0)
    {
        printf("\nQuantidade invalida!\n");
        return 0;
    }

    // Garante que a venda não exceda o estoque atual.
    if (quantidade > produtos[indiceProduto].quantidadeInicialEstoque)
    {
        printf("\nQuantidade indisponivel em estoque!\n");
        return 0;
    }

    // Se tudo estiver correto, realiza a baixa no estoque e incrementa o contador do cliente.
    produtos[indiceProduto].quantidadeInicialEstoque -= quantidade;
    clientes[indiceCliente].totalVendas += 1;

    // Armazena a venda na lista.
    vendas[*qtdVendas].id = *qtdVendas + 1;
    strcpy(vendas[*qtdVendas].data, data);
    strcpy(vendas[*qtdVendas].cpf, cpf);
    vendas[*qtdVendas].idProduto = idProduto;
    vendas[*qtdVendas].quantidade = quantidade;

    (*qtdVendas)++;

    printf("\nVenda registrada com sucesso!\n");
    return 1;
}

// Função para listar o histórico completo de vendas.
// Para cada venda, exibe os dados da transação e também o nome do cliente e do produto associado.
void listarVendas(struct Venda vendas[], int qtdVendas, struct Cliente clientes[], int qtdClientes, struct Produtos produtos[], int qtdProdutos)
{
    if (qtdVendas == 0)
    {
        printf("\nNenhuma venda cadastrada!\n");
        return;
    }

    printf("\n========= HISTORICO DE VENDAS =========\n");

    for (int i = 0; i < qtdVendas; i++)
    {
        int indiceCliente = buscarClientePorCPF(clientes, qtdClientes, vendas[i].cpf);
        int indiceProduto = buscarProdutoPorID(produtos, qtdProdutos, vendas[i].idProduto);

        printf("\nID da venda: %d\n", vendas[i].id);
        printf("Data: %s\n", vendas[i].data);

        if (indiceCliente != -1)
        {
            printf("CPF: %s\n", vendas[i].cpf);
            printf("Cliente: %s\n", clientes[indiceCliente].nome);
        }
        else
        {
            printf("CPF: %s\n", vendas[i].cpf);
            printf("Cliente: Nao encontrado\n");
        }

        if (indiceProduto != -1)
        {
            printf("ID do produto: %d\n", vendas[i].idProduto);
            printf("Produto: %s\n", produtos[indiceProduto].nome);
        }
        else
        {
            printf("ID do produto: %d\n", vendas[i].idProduto);
            printf("Produto: Nao encontrado\n");
        }
    }
}

// Função para salvar todas as vendas em um arquivo binário.
// Isso preserva os dados mesmo depois de fechar o programa.
void salvarVendas(struct Venda vendas[], int qtdVendas)
{
    FILE *arquivo = fopen("vendas.dat", "wb");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir arquivo de vendas!\n");
        return;
    }

    fwrite(&qtdVendas, sizeof(int), 1, arquivo);
    fwrite(vendas, sizeof(struct Venda), qtdVendas, arquivo);

    fclose(arquivo);
}

// Função para carregar as vendas salvas anteriormente.
// Se o arquivo não existir, a quantidade de vendas é iniciada como zero.
void carregarVendas(struct Venda vendas[], int *qtdVendas)
{
    FILE *arquivo = fopen("vendas.dat", "rb");

    if (arquivo == NULL)
    {
        *qtdVendas = 0;
        return;
    }

    fread(qtdVendas, sizeof(int), 1, arquivo);
    fread(vendas, sizeof(struct Venda), *qtdVendas, arquivo);

    fclose(arquivo);
}
