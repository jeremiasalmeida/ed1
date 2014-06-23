#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "movi_functions.h"
#include "print_format.h"
#include "cc_functions.h"
#include "input_functions.h"

/*
 * insere uma nova movimentação a uma lista dada
 */
struct movi* newMovi(char tipo[1], float valor)
{
    struct movi* novo = (struct movi*) malloc(sizeof(struct movi));
    strcpy(novo->tipo,tipo);
    novo->valor = valor;
    novo->proximo = NULL;
    return novo;
}

void insertMovi(struct movi** root,struct movi* novo)
{
    //iniciar a procura pelo último item
    if(!(*root))
    {
        (*root) = novo;
    }
    else
    {
        insertMovi(&(*root)->proximo, novo);
    }
}

/*
 * Faz a coleta das informacoes necessarias para uma nova movimentacao
 */
struct movi* getData_movi()
{
    int teste=0;
    char tipo[] = "\0";
    float valor = 0;
    
    while(strcmp(tipo,"\0") == 0)
    {
        print_bold("Entre com tipo da operacao (D=Deposito; S=Saque; T=Transferencia)");
        scanf("%s%*c",tipo);
        if((strcmp(tipo,"D") != 0) && (strcmp(tipo,"S") != 0) && (strcmp(tipo,"T") != 0))
        {
            print_red("Opcao invalida.");
            strcpy(tipo,"\0");
        }
        else{printf("Opcao %s selecionada.\n",tipo);}
    }
    
    while((!teste) && (valor==0.00))
    {
        print_bold("Entre com o valor:");
        teste = getInutFloat(&valor);
        
        if((valor == 0))
        {
            print_red("Valor inserido não é válido.");
            valor = 0.00;
        }
        
        
        if(strcmp(tipo,"D"))     {return newDeposito(valor);}
        else if(strcmp(tipo,"S")){return saque(valor);}
        else if(strcmp(tipo,"T")){print_alert("implementar transferencia");}
        
        if((strcmp(tipo,"S") == 0) && (valor > 0))
        {
            valor = -1*valor;
        }
    }
}
/*
 * Cria uma movimentação de deposito
 */
struct movi* newDeposito(float valor)
{
    if(valor < 0.00)
    {
        valor = -1*valor;
    }
    return newMovi("D",valor);
}
void getDepositoData(struct cc* raiz, int id)
{
    struct cc* node = findById(raiz,id);
    if(node)
    {
        float valor = 0;
        int teste;
        print_bold("Entre com o valor a ser depositado: ");
        teste = getInutFloat(&valor);
        if(teste==0){print_alert("Valor de input não compatível");return;}
        insertMovi(&(node)->raiz,newDeposito(valor));
        printf("Valor a ser depositado: %d na conta: %d",valor,id);
        
        node->ultima_tipo = "D";
        node->ultima_data = getDateAtual();
        node->ultima_valor = valor;
        node->saldo_atual = node->saldo_atual + valor;
        
    }
    else
    {
        print_alert("Conta não encontrada.");
    }
}

/*
 * Cria uma movimentação de saque
 */
struct movi* newSaque(float valor)
{
    if(valor > 0.00)
    {
        valor = -1*valor;
    }
    return newMovi("S",valor);
}

struct movi* transferencia()
{
    
}


/*
 * Printa a movimentação de uma lista dada.
 */
void print_movi(struct movi* root)
{
    if(!(root)) return;
    printf("(Tipo: %s | Valor: %.2f) -> ",root->tipo,root->valor);
    print_movi(root->proximo);
}

struct tm* getDateAtual()
{
    time_t currentTime;
    struct tm* timeinfo;
    
    /* Pega a hora atual do sistema e a converte em uma estrutura tm. */
    time(&currentTime);
    timeinfo = localtime(&currentTime);

    mktime(timeinfo);

    return timeinfo;
}

struct tm* getParaData(int dia, int mes, int ano)
{
    time_t currentTime;
    struct tm *timeinfo;
    
    /* Pega a hora atual do sistema e a converte em uma estrutura tm. */
    time(&currentTime);
    timeinfo= localtime(&currentTime);
    
    timeinfo->tm_mday= dia;
    timeinfo->tm_mon= mes - 1;
    timeinfo->tm_year= ano - 1900;
    
    mktime(timeinfo);

    return timeinfo;
}

struct movi* getLastMovi(struct movi* root)
{
    if(root)
    {
        if(!(root->proximo)){return root;}
        return getLastMovi(root->proximo);
    }
    else
    {
       return NULL; 
    }
}

void printLastMovi(struct cc* root,int id)
{
    struct cc* node = findById(root,id);
    if(node)
    {
        struct movi* lastMovi = getLastMovi(root->raiz);
        if((lastMovi))
        {
            printf("\n===========================\n");
            printf("Tipo: %c\nValor: %.3f",lastMovi->tipo,lastMovi->valor);
            printf("\n===========================\n");
        }
        else
        {
            print_alert("Movimentações vazias");
        }
    }
    else
    {
        print_alert("Conta não encontrada");
    }
}

void getDataSaque(struct cc* root,int id)
{
    struct cc* node = findById(root,id);
    if(node)
    {
        float valor=0;
        int teste=0;
        print_bold("Entre com o valor a ser sacado: ");
        teste = getInutFloat(&valor);
        if(teste<=0){print_alert("Valor passado invalido");return;}
        if((node->saldo_atual < valor) &&  strcmp(node->tipo_conta,"C"))
        {
            print_alert("Saldo atual menor que");return;
        }
        else if(strcmp(node->tipo_conta,"E") && ((node->saldo_atual-valor) < 1500.00))
        {
            print_alert("Saldo especial estourado. Saque não realizado");return;
        }
        
        insertMovi(&(node)->raiz,newSaque(valor));
        printf("Valor a ser depositado: %d na conta: %d",valor,id);
        
        node->ultima_tipo = "S";
        node->ultima_data = getDateAtual();
        node->ultima_valor = valor;
        node->saldo_atual = node->saldo_atual - valor;
    }
    else
    {
        print_alert("Conta não encontrada");
    }
}

int saldoAtual(struct cc* raiz,int id)
{
    struct cc* node = findById(raiz,id);
    if(node)
    {
        return node->saldo_atual;
    }
    else
    {
        print_bold("Conta não encontrada");
    }
    
            
}

void getTransferencia(struct cc* raiz,int id, int idDest)
{
    struct cc* node = findById(raiz,id);
    struct cc* destNode = findById(raiz,idDest);
    
    if((node) && (destNode))
    {
        int teste;float valor;
        print_bold("Valor da transferencia: ");
        teste = getInutFloat(&valor);
        if(teste==0){print_alert("Valor de entrada invalido");return;}
        insertMovi(node,newSaque(valor));
        insertMovi(destNode,newDeposito(valor));
        
        /*repetindo demais, se der tempo modificar esta rotina*/
        node->ultima_tipo = "S";
        node->ultima_data = getDateAtual();
        node->ultima_valor = valor;
        node->saldo_atual = node->saldo_atual - valor;
        
        destNode->ultima_tipo = "D";
        destNode->ultima_data = getDateAtual();
        destNode->ultima_valor = valor;
        destNode->saldo_atual = node->saldo_atual + valor;
        /*end*/
    }
    else
    {
        print_alert("Combinação de contas invalidas");
    }
}
