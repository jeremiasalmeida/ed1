#include <stdio.h>
#include <stdlib.h>
#include "cc_functions.h"
#include "movi_functions.h"
#define testenum 20

int main()
{
    int i=0;
    print_red("ATENÇÃO");
    print_alert("Todos os valores inseridos no programa serao considerados em modulo.");
        
    struct movi* root = newMovi("D",1200.00);
    printf("%s",root->tipo);
    //print_movi(root);
    //insertMovi(root,newMovi("S",1000.00));
    //print_movi(root);
    
    
    return 0;
}


/*
 * TODO: a) registro de conta corrente
 * TODO: b) leitura de conta corente
 * TODO: c) procura conta corrente
 * TODO: d) retornar o proximo id de conta corrente
 * TODO: e) cria nova conta corrent
 * TODO: f) alterar dados de conta corrente
 * TODO: g) fazer depositos
 * TODO: h) fazer saque conta corrente
 * TODO: i) pega saldo atual de uma conta corrente
 * TODO: j) dados da ultima movimentação de uma conta corrent
 * TODO: k) transferencia entre contas correntes
 */