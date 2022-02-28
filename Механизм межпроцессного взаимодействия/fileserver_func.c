#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fileserver.h"
int func_rashet(char *str, int len, char *str_1)
{
    int answer;
    int operand_2;
    char operation[10] = "+-*/";
    char *pch = strtok(str, operation);
    int operand_1 = atoi(pch);
    while (pch != NULL)
    {
        pch = strtok(NULL, operation);
        if (pch != NULL)
        {
            operand_2 = atoi(pch);
        }
    }
    if (strstr(str_1, "+"))
    {
        answer = operand_1 + operand_2;
    }
    if (strstr(str_1, "-"))
    {
        answer = operand_1 - operand_2;
    }
    if (strstr(str_1, "*"))
    {
        answer = operand_1 * operand_2;
    }
    if (strstr(str_1, "/"))
    {
        answer = operand_1 / operand_2;
    }
    return answer;
}