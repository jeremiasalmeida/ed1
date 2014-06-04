#include <stdio.h>
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
    
    while(valor==0)
    {
        scanf("%f",&valor);
        if((valor == 0))
        {
            print_red("Valor inserido nao e valido.");
            valor = 0.00;
        }
        
        if( ((strcmp(tipo,"T") == 0) || (strcmp(tipo,"D") == 0)) && (valor < 0.00))
        {
            valor = -1*valor;
        }
        else if((strcmp(tipo,"S") == 0) && (valor > 0))
        {
            valor = -1*valor;
        }
    }
    return newMovi(tipo,valor);
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