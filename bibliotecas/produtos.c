#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "estruturas.h"
#define TAM 100

//FUNCAO LIMPAR BUFFER
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // Limpa o buffer de entrada
    }
}       

void incluirProduto(struct Produtos produtos[], int *qtdProdutos)
{
    if (*qtdProdutos >= TAM)
    {
        printf("\nLimite de produtos atingido!\n");
        return;
    }

    int i = *qtdProdutos;

    produtos[i].id = i + 1;

    limparBuffer();

    printf("\nDigite o nome do produto: ");
    fgets(produtos[i].nome, 20, stdin);
    produtos[i].nome[strcspn(produtos[i].nome, "\n")] = '\0';

    printf("Digite a quantidade em estoque: ");
    scanf("%d", &produtos[i].quantidadeInicialEstoque);

    printf("Digite o preco: ");
    scanf("%f", &produtos[i].preco);

    (*qtdProdutos)++;

    printf("\nProduto cadastrado com sucesso!\nO ID do produto eh: %d\n\n", produtos[i].id);

}

void excluirProduto(struct Produtos produtos[], int *qtdProdutos)
{
    int idExcluir;

    printf("Digite o ID do produto: ");
    scanf("%d", &idExcluir);

    for (int i = 0; i < *qtdProdutos; i++)
    {
        if (produtos[i].id == idExcluir)
        {
            for (int j = i; j < *qtdProdutos - 1; j++)
            {
                produtos[j] = produtos[j + 1];
            }

            (*qtdProdutos)--;

            printf("Produto excluido com sucesso!\n");
            return;
        }
    }

    printf("Produto nao encontrado!\n");
}

void listarProdutos(struct Produtos produtos[], int qtdProdutos)
{
    if (qtdProdutos == 0)
    {
        printf("\nNenhum produto cadastrado!\n");
        return;
    }

    printf("\n========= LISTA DE PRODUTOS =========\n");

    for (int i = 0; i < qtdProdutos; i++)
    {
        printf("\nID: %d\n", produtos[i].id);
        printf("Nome: %s\n", produtos[i].nome);
        printf("Quantidade: %d\n", produtos[i].quantidadeInicialEstoque);
        printf("Preco: R$ %.2f\n", produtos[i].preco);
    }
}

void atualizarEstoque(struct Produtos produtos[], int qtdProdutos)
{
    int id, quantidade, opcao;

    printf("\nDigite o ID do produto: ");
    scanf("%d", &id);

    for (int i = 0; i < qtdProdutos; i++)
    {
        if (produtos[i].id == id)
        {
            printf("\nProduto: %s\n", produtos[i].nome);
            printf("Estoque atual: %d\n", produtos[i].quantidadeInicialEstoque);

            printf("\n1 - Entrada de estoque");
            printf("\n2 - Saida de estoque");
            printf("\nEscolha: ");
            scanf("%d", &opcao);

            printf("Quantidade: ");
            scanf("%d", &quantidade);

            if (opcao == 1)
            {
                produtos[i].quantidadeInicialEstoque += quantidade;
            }
            else if (opcao == 2)
            {
                if (quantidade <= produtos[i].quantidadeInicialEstoque)
                    produtos[i].quantidadeInicialEstoque -= quantidade;
                else
                    printf("Quantidade insuficiente em estoque!\n");
            }
            else
            {
                printf("\nOpcao invalida!\n");
            }

            return;
        }
    }

    printf("Produto nao encontrado!\n");
}

void buscarProduto(struct Produtos produtos[], int qtdProdutos)
{
    int id;

    printf("\nDigite o ID do produto: ");
    scanf("%d", &id);

    for (int i = 0; i < qtdProdutos; i++)
    {
        if (produtos[i].id == id)
        {
            printf("\n===== PRODUTO ENCONTRADO =====\n");
            printf("ID: %d\n", produtos[i].id);
            printf("Nome: %s\n", produtos[i].nome);
            printf("Quantidade: %d\n", produtos[i].quantidadeInicialEstoque);
            printf("Preco: R$ %.2f\n", produtos[i].preco);

            return;
        }
    }

    printf("Produto nao encontrado!\n");
}

void calcularValorEstoque(struct Produtos produtos[], int qtdProdutos)
{
    float total = 0;

    for (int i = 0; i < qtdProdutos; i++)
    {
        total += produtos[i].preco * produtos[i].quantidadeInicialEstoque;
    }

    printf("\nValor total do estoque: R$ %.2f\n", total);
}

void relatorioEstoqueBaixo(struct Produtos produtos[], int qtdProdutos)
{
    int encontrou = 0;

    printf("\n======= ESTOQUE BAIXO =======\n");

    for (int i = 0; i < qtdProdutos; i++)
    {
        if (produtos[i].quantidadeInicialEstoque < 10)
        {
            encontrou = 1;

            printf("\nID: %d\n", produtos[i].id);
            printf("Nome: %s\n", produtos[i].nome);
            printf("Quantidade: %d\n", produtos[i].quantidadeInicialEstoque);
        }
    }

    if (!encontrou)
        printf("Nenhum produto com estoque baixo.\n");
}

//Função para armazenar dados dos produtos

void salvarProdutos(struct Produtos produtos[], int qtdProdutos)
{
    FILE *arquivo;

    arquivo = fopen("produtos.dat", "wb");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir arquivo!\n");
        return;
    }

    fwrite(&qtdProdutos, sizeof(int), 1, arquivo);
    fwrite(produtos, sizeof(struct Produtos), qtdProdutos, arquivo);

    fclose(arquivo);
}

//Função para carregar dados dos produtos existentes

void carregarProdutos(struct Produtos produtos[], int *qtdProdutos)
{
    FILE *arquivo;

    arquivo = fopen("produtos.dat", "rb");

    if (arquivo == NULL)
    {
        *qtdProdutos = 0;
        return;
    }

    fread(qtdProdutos, sizeof(int), 1, arquivo);
    fread(produtos, sizeof(struct Produtos), *qtdProdutos, arquivo);

    fclose(arquivo);
}
