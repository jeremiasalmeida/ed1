#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cc_functions.h"
#include "movi_functions.h"

/*
 * Retorna a altura de uma arvore.
 */
int height(struct cc* N)
{
    if (N == NULL)
        return 0;
    return N->altura;
}
 
/*
 * Helper para trazer o maior valor entre dois inteiros
 */
int max(int a, int b)
{
    return (a > b)? a : b;
}
 
/*
 * Cria uma nova cc para ser adicionada a arvore.
 * Com esta centralização da criação de itens cc é possivel controlar prever o comportamento de todos os itens
 * da struct cc
 */
struct cc* newNode(int key)
{
    struct cc* cc = (struct cc*) malloc(sizeof(struct cc));
    //TODO acrescentar todos os campos de cc
    cc->esquerda   = NULL;
    cc->direita  = NULL;
    cc->altura = 1;  // new node is initially added at leaf
    return(cc);
}
 
/*
 * Faz a rotação a direita de uma arvore
 */
struct cc* rightRotate(struct cc* y)
{
    struct cc* x = y->esquerda;
    struct cc* T2 = x->direita;
 
    // Perform rotation
    x->direita = y;
    y->esquerda = T2;
 
    // Update heights
    y->altura = max(height(y->esquerda), height(y->direita))+1;
    x->altura = max(height(x->esquerda), height(x->direita))+1;
 
    // Return new root
    return x;
}
 
/*
 * Faz a rotação a esquerda de uma arvore.
 */
struct cc* leftRotate(struct cc* x)
{
    struct cc* y = x->direita;
    struct cc* T2 = y->esquerda;
 
    // Perform rotation
    y->esquerda = x;
    x->direita = T2;
 
    //  Update heights
    x->altura = max(height(x->esquerda), height(x->direita))+1;
    y->altura = max(height(y->esquerda), height(y->direita))+1;
 
    // Return new root
    return y;
}
 
/*
 * Retornar o valor de balanceamento de um ponto.
 */
int getBalance(struct cc* N)
{
    if (N == NULL)
        return 0;
    return height(N->esquerda) - height(N->direita);
}

/*
 * Esta função tem a finalidade de funcionar como um 'model' dos dados de uma conta corrente. Ela terá que saber:
 * Quais dados uma conta corrente precisa possuir;
 * Validar os dados de entrada do usuário;
 * Fazer as devidas chamadas para funções que saibam criar pontos e que fazer a inserção na arvore;
 */
struct cc* getData()
{
    //Todos os dados são necessários
    char nome[40] = "", senha[6] = "", //login/nome e senha
            cpf[12] = "", rg[10] = "", //documentos
            nascimento[10] = "", abertura[10] = "", ultima[10] = "", //datas
            tipo_conta, tipo_mov; //char únicos
    struct movi* raiz = (struct movi*) malloc(sizeof(struct movi)); //deposito inicial
    //abre para entrada do nome
    printf(">>> %d",strcmp(nome,""));
/*
 * Nome: nome do cliente (formato: caracter com 40 posições);
 * Senha: senha do cliente (formato: caracter com 6 posições);
 * CPF: cadastro de pessoa física (formato: caracter com 12 posições);
 * RG: registro geral (formato: caracter com 10 posições);
 * Data de nascimento: data de nascimento do cliente (formato: caracter com 10 posições);
 * Data de abertura: data em que o cliente realizou a abertura da conta corrente (formato: caracter com 10 posições);
 * Depósito inicial: valor inicial de depósito (formato: real); tipo da conta: pode ser especial (E),
 * quando o depósito inicial for superior a R$12.000,00, e comum (C), caso contrário (formato: 1 caracter);
 * Saldo atual: valor do saldo atual (formato: real);
 * Data da última movimentação: data da última movimentação realizada pelo cliente sobre a conta corrente
 * (formato: caracter com 10 posições);
 * Tipo da movimentação: tipo da última movimentação (D – débito; C – crédito) (formato: 1 caracter);
 */
}

/*
 * Faz toda a rotina de inserção de um novo item na arvore de contas correntes.
 * Também cuida para que a após a inserção a arvore permaneça balanceada.
 */
struct cc* insert(struct cc* node, int id)
{
    /* 1.  Perform the normal BST rotation */
    if (node == NULL)
        return(newNode(id));
 
    if (id < node->id)
        node->esquerda  = insert(node->esquerda, id);
    else
        node->direita = insert(node->direita, id);
 
    /* 2. Update height of this ancestor node */
    node->altura = max(height(node->esquerda), height(node->direita)) + 1;
 
    /* 3. Get the balance factor of this ancestor node to check whether
       this node became unbalanced */
    int balance = getBalance(node);
 
    // If this node becomes unbalanced, then there are 4 cases
 
    // Left Left Case
    if (balance > 1 && id < node->esquerda->id)
        return rightRotate(node);
 
    // Right Right Case
    if (balance < -1 && id > node->direita->id)
        return leftRotate(node);
 
    // Left Right Case
    if (balance > 1 && id > node->esquerda->id)
    {
        node->esquerda =  leftRotate(node->esquerda);
        return rightRotate(node);
    }
 
    // Right Left Case
    if (balance < -1 && id < node->direita->id)
    {
        node->direita = rightRotate(node->direita);
        return leftRotate(node);
    }
 
    /* return the (unchanged) node pointer */
    return node;
}
 
/*
 * Função para printar na tela em pre-orderm a arvore de contas correntes.
 */
void preOrder(struct cc* root)
{
    if(root != NULL)
    {
        printf("%d ", root->id);
        preOrder(root->esquerda);
        preOrder(root->direita);
    }
}