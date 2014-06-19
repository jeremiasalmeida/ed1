#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "movi_functions.h"
#include "print_format.h"

/*
 * insere uma nova movimentação a uma lista dada
 */
struct movi* newMovi(char* tipo, float valor)
{
    struct movi* novo = (struct movi*) malloc(sizeof(struct movi));
    novo->tipo = tipo;
    novo->valor = valor;
    novo->proximo = NULL;
    return novo;
}

struct movi* insertMovi(struct movi** root,struct movi* novo)
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
        
        
        if(strcmp(tipo,"D"))     {return deposito(valor);}
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
struct movi* deposito(float valor)
{
    if(valor < 0.00)
    {
        valor = -1*valor;
    }
    return newMovi("D",valor);
}

/*
 * Cria uma movimentação de saque
 */
struct movi* saque(float valor)
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