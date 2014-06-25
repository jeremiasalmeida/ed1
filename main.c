#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cc_functions.h"
#include "movi_functions.h"
#include "print_format.h"
#include "input_functions.h"
#define testenum 20

int main()
{
    int i=-2,teste,op=-1,idHolder,idHolder2;
    int idDest;
    char passwd[10];
    struct cc* root = NULL;
    print_red("ATENÇÃO");
    print_alert("Os modulos dos valores inseridos no programa serão automaticamente ajustados de acordo com a acao.");
    
    //raiz = insert(raiz, newNode(), findNextId(raiz));
    
    while(i != -1)
    {
        print_green("Informe o numero da conta corrente: ");
        teste = getInutInt(&i);
        if(teste==0){print_alert("Entrada invalida");i=-2;}
        else{
            if(i!=-1){
                print_bold("Entre com a senha:");
                teste = getInutString(passwd);
                if(teste==0){print_alert("Entrada invalida");i=-2;}
                else{
                    if((i==0) && (strcmp(passwd,"12345") == 0))
                    {
                        while(op!=0)
                        {
                            print_alert("Funcionario autenticado!");
                        
                            print_bold("Escolha uma opção:");
                            printf("0 - Sair (Opção padrão)\n1 - cadastrar uma conta corrente\n");
                            printf("2 - excluir uma conta corrente;\n3 - alterar os dados da conta corrente;\n");
                            printf("4 - consultar dados da conta corrente;\n5 - realizar depósito em conta corrente;\n");
                            printf("6 - efetivar saque em conta corrente;\n7 - consultar saldos;\n");
                            printf("8 - realizar a transferência entre contas correntes;\n9 - consultar os dados da última movimentação.\n");

                            teste = getInutInt(&op);
                            if(teste==0){print_alert("Entrada invalida");op=-1;}

                            switch(op)
                            {
                                case 1:
                                    root = insert(root,getData(),findNextId(root));
                                    break;
                                case 2:
                                    print_bold("Entre com o Id da conta: ");
                                    teste = getInutInt(&idHolder);
                                    removeAcc(root,idHolder);
                                    break;
                                case 3:
                                    print_bold("Entre com o Id da conta: ");
                                    teste = getInutInt(&idHolder);
                                    alterCCdata(findById(root,idHolder));
                                    break;
                                case 4:
                                    print_bold("Entre com o Id da conta: ");
                                    teste = getInutInt(&idHolder);
                                    printCcdata(root,idHolder);
                                    break;
                                case 5:
                                    print_bold("Entre com o Id da conta: ");
                                    teste = getInutInt(&idHolder);
                                    getDepositoData(root,idHolder);
                                    break;
                                case 6:
                                    print_bold("Entre com o Id da conta: ");
                                    teste = getInutInt(&idHolder);
                                    getDataSaque(root,idHolder);
                                    break;
                                case 7:
                                    print_bold("Entre com o Id da conta: ");
                                    teste = getInutInt(&idHolder);
                                    printLastMovi(root,idHolder);
                                    break;
                                case 8:
                                    print_bold("Entre com o Id-origem da conta: ");
                                    teste = getInutInt(&idHolder);
                                    print_bold("Entre com o Id-destino da conta: ");
                                    teste = getInutInt(&idHolder2);
                                    getTransferencia(root,idHolder,idHolder2);
                                    break;
                                case 9:
                                    print_bold("Entre com o Id-origem da conta: ");
                                    teste = getInutInt(&idHolder);
                                    printLastMovi(root,idHolder);
                                    break;
                                case 0:
                                default:
                                    print_alert("Saindo");
                                    op=0;
                                    break;        
                            }
                        }
                        op=-1;
                   }
                   else{
                       struct cc* node = findById(root,i);
                       if((node)){
                           if(strcmp(node->senha,passwd)==0 && (strcmp(node->status,"A")==0))
                           {
                               while(op!=0)
                               {
                                   print_bold("Escolha uma opção");
                                   printf("0 - Sair (Opção padrão)\n1 - realizar depósito em conta corrente\n2 - efetivar saque em conta corrente\n");
                                   printf("3 - consultar saldos\n4 - realizar a transferência entre contas correntes;\n");
                                   printf("5 - consultar os dados da última movimentação\n");
                                   teste = getInutInt(&op);
                                   if(teste==0){print_alert("Entrada invalida");op=-1;}
                                   switch(op)
                                   {
                                       case 1:
                                           getDepositoData();
                                           break;
                                       case 2:
                                           getDataSaque();
                                           break;
                                       case 3:
                                           saldoAtual(root,i);
                                           break;
                                       case 4:
                                           print_bold("Conta destino:");
                                           teste = getInutInt(&idDest);
                                           if(teste==0){print_alert("Entrada invalida");}
                                           else{getTransferencia(root,i,idDest);}
                                           break;
                                       case 5:
                                           printLastMovi(root,i);
                                           break;
                                       case 0:
                                       default:
                                           op=0;
                                           break;        
                                   }
                               }
                               op=-1;
                           }
                           else
                           {
                               print_alert("Dados informados incorretos.");
                           }
                       }
                       else{
                           print_alert("Dados informados incorretos.");
                       }
                   }
                   
                }
            }
        }
    }
    
    return 0;
}