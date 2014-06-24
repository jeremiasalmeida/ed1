/* 
 * File:   movi_functions.h
 * Author: careers
 *
 * Created on June 3, 2014, 00:40 AM
 */

#ifndef MOVI_FUNCTIONS_H
#define	MOVI_FUNCTIONS_H

/*
 * Esta estrutura não pode ser em forma de arvore, pois irá dificultar a saida de dados e calculo
 * do saldo das contas, uma vez que esta estrutura não vai ter muita buscas não vale a pena ser em formato de
 * arvore binária de busca
 */
struct movi
{
    int id;
    char tipo[1];
    float valor;
    struct movi* proximo;
};


/*
 * insere uma nova movimentação a uma lista dada
 */
struct movi* newMovi(char tipo[], float valor);

/*
 * insere uma nova movimentação a uma lista dada
 */
extern void insertMovi(struct movi** root,struct movi* novo);

/*
 * Printa a movimentação de uma lista dada.
 */
extern void print_movi(struct movi* root);

/*
 * Faz a coleta das informacoes necessarias para uma nova movimentacao
 */
extern struct movi* getData_movi();

extern struct movi* newDeposito(float valor);

extern struct tm* getDateAtual();
extern void clearMovi(struct movi* root);
/*
 * Cria uma movimentação de saque
 */
extern struct movi* newSaque(float valor);

extern struct movi* transferencia();
extern struct movi* getLastMovi(struct movi* root);

#endif	/* MOVI_FUNCTIONS_H */