#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fileserver.h"
int func_check(char *str)
{
    int flag = 0;
    if (strstr(str, "+"))
    {
        flag = 1;
    }
    if (strstr(str, "-"))
    {
        flag = 1;
    }
    if (strstr(str, "*"))
    {
        flag = 1;
    }
    if (strstr(str, "/"))
    {
        flag = 1;
    }
    return flag;
}