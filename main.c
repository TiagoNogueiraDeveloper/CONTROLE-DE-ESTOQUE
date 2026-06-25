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
#include "bibliotecas/vendas.c"

int main(){

    int opcao;

    struct Produtos produtos[100];
    int qtdProdutos = 0;
    carregarProdutos(produtos, &qtdProdutos);

    struct Cliente clientes[100];
    int qtdClientes = 0;
    carregarClientes(clientes, &qtdClientes);

    struct Venda vendas[100];
    int qtdVendas = 0;
    carregarVendas(vendas, &qtdVendas);

do
    {
        opcao = menuGeral(); // Chama o menu geral e armazena a opção escolhida pelo usuário

        switch(opcao)
        {
            //================== MENU PRODUTOS ==================
            case 1:
            {
                int opProd;

                do
                {
                    opProd = menuProdutos();

                    switch(opProd)
                    {
                        case 1:
                            incluirProduto(produtos, &qtdProdutos);
                            salvarProdutos(produtos, qtdProdutos);
                            break;

                        case 2:
                            excluirProduto(produtos, &qtdProdutos);
                            salvarProdutos(produtos, qtdProdutos);
                            break;

                        case 3:
                            listarProdutos(produtos, qtdProdutos);
                            break;

                        case 4:
                            atualizarEstoque(produtos, qtdProdutos);
                            salvarProdutos(produtos, qtdProdutos);
                            break;

                        case 5:
                            buscarProduto(produtos, qtdProdutos);
                            break;

                        case 6:
                            calcularValorEstoque(produtos, qtdProdutos);
                            break;

                        case 7:
                            relatorioEstoqueBaixo(produtos, qtdProdutos);
                            break;

                        case 0:
                            printf("\nVoltando ao Menu Geral...\n");
                            salvarProdutos(produtos, qtdProdutos);
                            break;

                        default:
                            printf("\nOpcao invalida!\n");
                    }

                } while(opProd != 0);

                break;
            }

            //================== MENU CLIENTES ==================
            case 2:
            {
                int opCliente;

                do
                {
                    opCliente = menuClientes();

                    switch(opCliente)
                    {
                        case 1:
                            incluirCliente(clientes, &qtdClientes);
                            salvarClientes(clientes, qtdClientes);
                            break;

                        case 2:
                            excluirCliente(clientes, &qtdClientes);
                            salvarClientes(clientes, qtdClientes);
                            break;

                        case 3:
                            listarClientes(clientes, qtdClientes);
                            break;

                        case 0:
                            printf("\nVoltando ao Menu Geral...\n");
                            salvarClientes(clientes, qtdClientes);
                            break;

                        default:
                            printf("\nOpcao invalida!\n");
                    }

                } while(opCliente != 0);

                break;
            }

            //================== MENU VENDAS ==================
            case 3:
            {
                int opVenda;

                do
                {
                    opVenda = menuVendas();

                    switch(opVenda)
                    {
                        case 1:
                            incluirVenda(vendas, &qtdVendas, clientes, qtdClientes, produtos, qtdProdutos);
                            salvarVendas(vendas, qtdVendas);
                            salvarProdutos(produtos, qtdProdutos);
                            salvarClientes(clientes, qtdClientes);
                            break;

                        case 2:
                            listarVendas(vendas, qtdVendas, clientes, qtdClientes, produtos, qtdProdutos);
                            break;

                        case 0:
                            printf("\nVoltando ao Menu Geral...\n");
                            break;

                        default:
                            printf("\nOpcao invalida!\n");
                    }

                } while(opVenda != 0);

                break;
            }
        }
    }while(opcao != 0);

return 0;   
}
    /*if (opcao == 2)
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
*/