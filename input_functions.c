#include <stdio.h>
#include "input_functions.h"
#define STRSIZE 130
/*
 * Captura strings do stdin
 */
int getInutChar(char *target)
{
    char buffer[ STRSIZE ];
    fgets(buffer, sizeof buffer, stdin);
    return sscanf(buffer," %[^\n]", target);
}

/*
 * Captura inteiros do stdin
 */
int getInutInt(int *target)
{
    char buffer[ STRSIZE ];
    fgets(buffer, sizeof buffer, stdin);
    return sscanf(buffer," %d", target);
}

int getInutFloat(float *target)
{
    char buffer[ STRSIZE ];
    fgets(buffer, sizeof buffer, stdin);
    return sscanf(buffer," %f", target);
}