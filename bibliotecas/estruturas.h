#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

// Estrutura que representa um cliente do sistema.
struct Cliente
{
    int id;
    char nome[50];
    char cpf[12];
    int totalVendas;
};

// Estrutura que representa um produto do sistema.
struct Produtos
{
    int id;
    char nome[20];
    int quantidadeInicialEstoque;
    float preco;
};

// Estrutura que representa uma venda do sistema.
struct Venda
{
    int id;
    char data[11];
    char cpf[12];
    int idProduto;
    int quantidade;
};

// Declarações de funções do módulo de clientes.
void limparBufferClientes(void);
void limparCpf(const char *entrada, char *saida);
int validarCPF(const char *cpf);
int cpfJaCadastrado(struct Cliente clientes[], int qtdClientes, const char *cpf);
void incluirCliente(struct Cliente clientes[], int *qtdClientes);
void excluirCliente(struct Cliente clientes[], int *qtdClientes);
void listarClientes(struct Cliente clientes[], int qtdClientes);
void salvarClientes(struct Cliente clientes[], int qtdClientes);
void carregarClientes(struct Cliente clientes[], int *qtdClientes);

// Declarações de funções do módulo de produtos.
void limparBuffer(void);
void incluirProduto(struct Produtos produtos[], int *qtdProdutos);
void excluirProduto(struct Produtos produtos[], int *qtdProdutos);
void listarProdutos(struct Produtos produtos[], int qtdProdutos);
void atualizarEstoque(struct Produtos produtos[], int qtdProdutos);
void buscarProduto(struct Produtos produtos[], int qtdProdutos);
void calcularValorEstoque(struct Produtos produtos[], int qtdProdutos);
void relatorioEstoqueBaixo(struct Produtos produtos[], int qtdProdutos);
void salvarProdutos(struct Produtos produtos[], int qtdProdutos);
void carregarProdutos(struct Produtos produtos[], int *qtdProdutos);

// Declarações de funções do módulo de vendas.
void limparBufferVendas(void);
int validarData(const char *data);
int incluirVenda(struct Venda vendas[], int *qtdVendas, struct Cliente clientes[], int qtdClientes, struct Produtos produtos[], int qtdProdutos);
void listarVendas(struct Venda vendas[], int qtdVendas, struct Cliente clientes[], int qtdClientes, struct Produtos produtos[], int qtdProdutos);
void salvarVendas(struct Venda vendas[], int qtdVendas);
void carregarVendas(struct Venda vendas[], int *qtdVendas);

#endif
