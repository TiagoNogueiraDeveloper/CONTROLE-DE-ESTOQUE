#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TAM 1
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

void incluirProduto(){

    struct Produtos produtos[TAM];
    for (int i = 0; i < TAM+1; i++)
    {   
        produtos[i].id = i+1;

        limparBuffer(); // Chama a função para limpar o buffer antes de ler a string

        printf("\nDigite o nome do produto: ");
        fgets(produtos[i].nome, 20, stdin);

        printf("\nDigite a quantidade inicial em estoque do produto: ");
        scanf("%d", &produtos[i].quantidadeInicialEstoque);

        limparBuffer(); // Chama a função para limpar o buffer antes de ler a string

        printf("\nDigite o preco do produto: ");
        scanf("%f", &produtos[i].preco);
    }
}

void excluirProduto(){

    struct Produtos produtos[TAM];
    int idExcluir;

    printf("\nDigite o ID do produto que deseja excluir: ");
    scanf("%d", &idExcluir);

    for (int i = 0; i < TAM+1; i++)
    {
        if (produtos[i].id == idExcluir && produtos[i].id != 0) // VERIFICAR SE JA HOUVE VENDA DO PRODUTO
        {
            produtos[i].id = 0;
            printf("\nProduto com ID %d excluido com sucesso.\n", idExcluir);
        }
        else 
        {
            printf("Produto inexsistente!!");
        }
    }
}
