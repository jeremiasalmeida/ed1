#include <stdio.h>
#include <stdlib.h>
#define testenum 20

struct movi
{
    int id;
    char tipo;
    float valor;
    struct movi* proximo;
};

struct cc
{
    int id;
    char nome[40], senha[6], cpf[12], rg[10], nascimento[10], abertura[10], ultima[10], tipo_conta, tipo_mov;
    float saldo_atual;
    struct cc* esquerda;
    struct cc* direita;
    struct movi* raiz;
};

/**
Nro. da conta corrente: número da conta corrente do cliente cadastrado (formato: inteiro);
Nome: nome do cliente (formato: caracter com 40 posições);
Senha: senha do cliente (formato: caracter com 6 posições);
CPF: cadastro de pessoa física (formato: caracter com 12 posições);
RG: registro geral (formato: caracter com 10 posições);
Data de nascimento: data de nascimento do cliente (formato: caracter com 10 posições);
Data de abertura: data em que o cliente realizou a abertura da conta corrente (formato: caracter com
10 posições);
Depósito inicial: valor inicial de depósito (formato: real);
Tipo da conta: pode ser especial (E), quando o depósito inicial for superior a R$12.000,00, e comum
(C), caso contrário (formato: 1 caracter);
Saldo atual: valor do saldo atual (formato: real);
Data da última movimentação: data da última movimentação realizada pelo cliente sobre a conta
corrente (formato: caracter com 10 posições);
Tipo da movimentação: tipo da última movimentação (D – débito; C – crédito) (formato: 1 caracter);
**/


int main()
{
    int i=0;
    struct cc* root = NULL;
    for(i = 0;i<=testenum;i++)
    {
        if(create_acc(&root))
        {
            printf("Conta %d criada com \e[32msucesso\e[0m\n",i);
        }
        else
        {
            printf("Conta %d\e[31m nao\e[0m criada\n",i);
        }
    }
    
    return 0;
}

int create_acc(struct cc** root)
{
    return 0;
}

/*
TODO: a) registro de conta corrente
 *      DONE: structs conta, movimentação
 *      TODO: cria conta
TODO: b) leitura de conta corrente
TODO: c) procura conta corrente
TODO: d) retornar o proximo id de conta corrente
TODO: e) cria nova conta corrent
TODO: f) alterar dados de conta corrente
TODO: g) fazer depositos
TODO: h) fazer saque conta corrente
TODO: i) pega saldo atual de uma conta corrente
TODO: j) dados da ultima movimentação de uma conta corrent
TODO: k) transferencia entre contas correntes
*/