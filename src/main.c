#include "datastructs.h"

int main(void)
{
    char CMD1[10], CMD2[10], CMD3[10];

    while(1) {
        scanf("%s", CMD1);
        scanf(" %s", CMD2);
        scanf(" %s", CMD3);
        if (strcmp(CMD1, "exit") == 0) 
            exit(0);
        else 
            LiveData_Decode(CMD1, CMD2, CMD3);
    }
}

