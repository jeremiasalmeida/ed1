#include <stdio.h>
#include <stdlib.h>
#include "cc_functions.h"
#include "movi_functions.h"
#include "print_format.h"
#define testenum 20

int main()
{
    int i=0;
    struct cc* raiz = NULL;
    print_red("ATENÇÃO");
    print_alert("O modulos dos valores inseridos no programa serão automaticamente ajustados de acordo com a acao.");
    
    getData();
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