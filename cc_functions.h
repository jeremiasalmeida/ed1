/* 
 * File:   cc_functions.h
 * Author: jeremias almeida
 *
 * Created on June 3, 2014, 00:26 AM
 */

#ifndef CC_FUNCTIONS_H
#define	CC_FUNCTIONS_H

/*
 * Nro. da conta corrente: número da conta corrente do cliente cadastrado (formato: inteiro);
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
struct cc
{
    int id, altura;
    char nome[40], senha[6], cpf[12], rg[10], nascimento[10], abertura[10], ultima[10], tipo_conta, tipo_mov;
    float saldo_atual;
    struct cc* esquerda;
    struct cc* direita;
    struct movi* raiz;
};


/*
 * Helper para trazer o maior valor entre dois inteiros
 */
extern int max(int a, int b);

/*
 * Retorna a altura de uma arvore.
 */
extern int height(struct cc* N);

/*
 * Função para printar na tela em pre-orderm a arvore de contas correntes.
 */
extern void preOrder(struct cc* root);

/*
 * Faz toda a rotina de inserção de um novo item na arvore de contas correntes.
 * Também cuida para que a após a inserção a arvore permaneça balanceada.
 */
extern struct cc* insert(struct cc* node, int id);

/*
 * Esta função tem a finalidade de funcionar como um 'model' dos dados de uma conta corrente. Ela terá que saber:
 * Quais dados uma conta corrente precisa possuir;
 * Validar os dados de entrada do usuário;
 * Fazer as devidas chamadas para funções que saibam criar pontos e que fazer a inserção na arvore;
 */
extern struct cc* getData();

/*
 * Retornar o valor de balanceamento de um ponto.
 */
extern int getBalance(struct cc* N);

/*
 * Faz a rotação a esquerda de uma arvore.
 */
extern struct cc* leftRotate(struct cc* x);

/*
 * Faz a rotação a direita de uma arvore
 */
extern struct cc* rightRotate(struct cc* y);

/*
  * Cria uma nova cc para ser adicionada a arvore.
 * Com esta centralização da criação de itens cc é possivel controlar prever o comportamento de todos os itens
 * da struct cc
 */
extern struct cc* newNode(int key);

#endif	/* CC_FUNCTIONS_H */