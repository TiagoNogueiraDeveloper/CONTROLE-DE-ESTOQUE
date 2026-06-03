// MODULARIZAÇÃO DOS MENUS UTILIZADOS NO PROJETO DE GERENCIAMENTO DE ESTOQUE DE PRODUTOS
#include <stdio.h>
int menuGeral(){
    int opcao;
    printf("Menu Geral:\n");
    printf("1. Gerenciamento de Produtos\n");
    printf("2. Cadastro de Clientes\n");
    printf("3. Registro de Vendas\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    return opcao;
}
int menuProdutos(){
    int opcaoProdutos;
    printf("Menu de Produtos:\n");
    printf("1. Adicionar Produto\n");
    printf("2. Remover Produto\n");
    printf("3. Listar Produtos\n");
    printf("4. Atualizar Estoque\n");
    printf("5. Buscar Produtos\n");
    printf("6. Calcular Valor do Estoque\n");
    printf("7. Relatório de Estoque Baixo\n");
    printf("0. Voltar ao Menu Geral\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcaoProdutos);
    return opcaoProdutos;
}

int menuClientes(){
    int opcaoClientes;
    printf("Menu de Clientes:\n");
    printf("1. Adicionar Cliente\n");
    printf("2. Remover Cliente\n");
    printf("3. Listar Clientes\n");
    printf("0. Voltar ao Menu Geral\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcaoClientes);
    return opcaoClientes;
}

int menuVendas(){
    int opcaoVendas;
    printf("Menu de Vendas:\n");
    printf("1. Registrar Venda\n");
    printf("2. Listar Vendas\n");
    printf("0. Voltar ao Menu Geral\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcaoVendas);
    return opcaoVendas;
}