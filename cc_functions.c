#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cc_functions.h"
#include "movi_functions.h"
#include "print_format.h"
#include "input_functions.h"

/*
 * Retorna a altura de uma arvore.
 */
int height(struct cc* acc)
{
    if (acc == NULL)
        return 0;
    return acc->altura;
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
struct cc* newNode()
{
    struct cc* node = (struct cc*) malloc(sizeof(struct cc));
    node->id   = -1;
    node->esquerda   = NULL;
    node->direita  = NULL;
    node->altura = 1;
    strcpy(node->status,"A");
    node->nascimento = getDateAtual();
    node->abertura = getDateAtual();
   
    return(node);
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
    int teste=0, dia=0, mes=0, ano=0;
    float valor=0.00;
    char nascimento[10], buffer[100];
    struct cc* node = newNode();
   
    //Inicia a entrada dos dados
    print_bold("Entre com o nome:");
    while(!teste)
    {
        teste = getInutChar(node->nome);
        if(!strcmp(node->nome,""))
        {
            print_alert("Nome não pode ser vazio");
            teste=0;
        }
    }
    
    teste=0;
    print_bold("Entre com a senha:");
    while(!teste)
    {
        teste = getInutChar(node->senha);
        if(!strcmp(node->senha,""))
        {
            print_alert("Senha não pode ser vazia");
            teste=0;
        }
    }
    
    teste=0;
    print_bold("Entre com CPF (apenas numeros):");
    while(!teste)
    {
        teste = getInutChar(node->cpf);
        if(!strcmp(node->cpf,""))
        {
            print_alert("CPF não pode ser vazio");
            teste=0;
        }
    }
    
    teste=0;
    print_bold("Entre com a RG (apenas numeros):");
    while(!teste)
    {
        teste = getInutChar(node->rg);
        if(!strcmp(node->rg,""))
        {
            print_alert("RG não pode ser vazio");
            teste=0;
        }
    }
    
    teste=0;
    print_bold("Entre com a Data de nascimento (dd/mm/aaaa):");
    while(!teste)
    {
        teste = getInutChar(nascimento);       
        
        if(!strcmp(nascimento,""))
        {
            print_alert("Data de nascimento não pode ser vazia");
            teste=0;
        }
        else if(teste)
        {
            sprintf(buffer, "%c%c", nascimento[0], nascimento[1]);
            sscanf(buffer,"%d",&dia);
            
            sprintf(buffer, "%c%c", nascimento[3], nascimento[4]);
            sscanf(buffer,"%d",&mes);
            
            sprintf(buffer, "%c%c%c%c", nascimento[6], nascimento[7], nascimento[8], nascimento[9]);
            sscanf(buffer,"%d",&ano);
            
            node->nascimento->tm_mday = dia;
            node->nascimento->tm_mon = mes-1;
            node->nascimento->tm_year = ano-1900;
        }
    }

    teste=0;
    print_bold("Entre com o valor de depósito inicial:");
    while(!teste)
    {
        teste = getInutFloat(&valor);
        node->raiz = newDeposito(valor);
        if(valor > 12000.00) {node->tipo_conta = 'E';}else{node->tipo_conta = 'C';}
        
        node->saldo_atual = valor;
        node->ultima_data = getDateAtual();
        strcpy(node->ultima_tipo,"D");
        node->ultima_valor = valor;
    }  
    return node;
}

/*
 * Faz toda a rotina de inserção de um novo item na arvore de contas correntes.
 * Também cuida para que a após a inserção a arvore permaneça balanceada.
 */
struct cc* insert(struct cc* node, struct cc* new, int id)
{
    struct cc* target = findById(node,id);
    if(target)
    {
        target->abertura = new->abertura;
        target->nascimento = new->nascimento;
        target->raiz = new->raiz;
        target->saldo_atual = new->saldo_atual;
        target->ultima_data = new->ultima_data;
        target->ultima_valor = new->ultima_valor;
        
        strcpy(target->status,"A");
        strcpy(target->cpf,new->cpf);
        strcpy(target->nome,new->nome);
        strcpy(target->rg,new->rg);
        strcpy(target->senha,new->senha);
        //strcpy(target->tipo_conta,new->tipo_conta);
        target->tipo_conta = new->tipo_conta;
        strcpy(target->ultima_tipo,new->ultima_tipo);
        
    }
    else if (id > 0)
    {
        if(!(node))
        {
            new->id = id;
            return new;
        }
        
        if (id < node->id)
            node->esquerda  = insert(node->esquerda, new, id);
        else
            node->direita = insert(node->direita, new, id);

        node->altura = max(height(node->esquerda), height(node->direita)) + 1;

        int balance = getBalance(node);

        if (balance > 1 && id < node->esquerda->id)
            return rightRotate(node);

        if (balance < -1 && id > node->direita->id)
            return leftRotate(node);

        if (balance > 1 && id > node->esquerda->id)
        {
            node->esquerda =  leftRotate(node->esquerda);
            return rightRotate(node);
        }

        if (balance < -1 && id < node->direita->id)
        {
            node->direita = rightRotate(node->direita);
            return leftRotate(node);
        }

        return node;
    }
    else
    {
        print_red("Impossível cadastrar mais clientes");
    }
}
 
/*
 * Função para printar na tela em pre-orderm a arvore de contas correntes.
 */
void preOrder(struct cc* root)
{
    if(root == NULL) return;
    printf("%d ",root->id);
    preOrder(root->esquerda);
    preOrder(root->direita);
}

int findNextId(struct cc* root)
{
    int id = NULL;
    id = getReUsebleId(root);
    if(id == NULL) return getMaiorId(root);
    else return id;
}
int getReUsebleId(struct cc* root)
{
    int ret = NULL;
    if(!(root))
    {
        return NULL;
    }
    else
    {
        if(strcmp(root->status,"E") == 0) return root->id;
        ret = findNextId(root->esquerda);
        if(ret == NULL) ret = findNextId(root->esquerda);
        return ret;
        
    }
}
int getMaiorId(struct cc* root)
{
    if(!(root)) return 1;
    if(!(root->direita)) return getMaiorId(root->direita);
    else return root->id + 1;
    
}

struct cc* findById(struct cc* node, int id)
{
    if(!(node)) return NULL;
    
    if(node->id == id) return node;
    
    if(id < node->id){return findById(node->esquerda,id);}else{return findById(node->direita,id);}
    
}

int removeAcc(struct cc* root, int id)
{
    struct cc* node = findById(root,id);
    if(node)
    {
        strcpy(node->status,"E");
        clearMovi(node->raiz);
    }
    else
    {
        print_alert("Conta invalida");
    }
}