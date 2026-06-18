#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TAM 100

struct Produtos 
{
    int id;
    char nome[20];
    int quantidadeInicialEstoque;
    float preco;
};

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

    printf("\nProduto cadastrado com sucesso!\nO ID do produto é: %d", produtos[i].id);

}

void excluirProduto(struct Produtos produtos[], int qtdProdutos)
{
    int idExcluir;

    printf("\nDigite o ID do produto que deseja excluir: ");
    scanf("%d", &idExcluir);

    for (int i = 0; i < qtdProdutos; i++)
    {
        if (produtos[i].id == idExcluir)
        {
            produtos[i].id = 0;

            printf("\nProduto excluido com sucesso!\n");
            return;
        }
    }

    printf("\nProduto nao encontrado!\n");
}

void listarProduto(struct Produtos produtos[], int qtdProdutos)
{
    
}


