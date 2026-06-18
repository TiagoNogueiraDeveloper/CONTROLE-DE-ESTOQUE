// CONTROLE DE ESTOQUE DE PRODUTOS
// 1. Módulo de Produtos: Gerenciamento do catálogo de produtos e níveis de
// estoque.
// 2. Módulo de Clientes: Cadastro de clientes.
// 3. Módulo de Vendas: Registro de vendas e inventário.
// REANAN CESAR MICHELON E TIAGO BRANDÃO NOGUEIRA 
// JUNHO DE 2026
#include <stdio.h>
#include "bibliotecas/menuEscolhas.c"
#include "bibliotecas/clientes.c"
#include "bibliotecas/produtos.c"

int main(){

    int opcao = menuGeral(); // Chama o menu geral e armazena a opção escolhida pelo usuário

    struct Produtos produtos[100];
    int qtdProdutos = 0;

    if (opcao == 1)
    {
        int opProd = menuProdutos();
        
        if (opProd == 1) // Chama o menu de produtos se a opção escolhida for 1
        {
            incluirProduto(produtos, &qtdProdutos); // Chama a função para incluir um produto se a opção escolhida for 1 no menu de produtos
        }
        else if (opProd == 2)
        {
            excluirProduto(produtos, qtdProdutos); // Chama a função para excluir um produto se a opção escolhida for 2 no menu de produtos
        }
    }
    else if (opcao == 2)
    {
        menuClientes(); // Chama o menu de clientes se a opção escolhida for 2
    }
    else if (opcao == 3)
    {
        menuVendas(); // Chama o menu de vendas se a opção escolhida for 3
    }
    else if (opcao == 0)
    {
        printf("Saindo do programa...\n"); // Exibe uma mensagem de saída se a opção escolhida for 0
    }
    else
    {
        printf("Opcao invalida. Por favor, escolha uma opcao valida.\n"); // Exibe uma mensagem de erro se a opção escolhida for inválida
    }
    
    return 0;
}