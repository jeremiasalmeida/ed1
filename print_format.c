#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Printa texto em bold
 */
void print_bold(char t[])
{
    printf("\e[1m%s\e[0m\n",t);
}

/*
 * Printa vermelho
 */
void print_red(char t[])
{
    printf("\e[31m%s\e[0m\n",t);
}

void print_green(char t[])
{
    printf("\e[32m%s\e[0m\n",t);
}

void print_yellow(char t[])
{
    printf("\e[33m%s\e[0m\n",t);
}

void print_alert(char t[])
{
    printf("\e[1;47;5;31m%s\e[0m\n",t);
}