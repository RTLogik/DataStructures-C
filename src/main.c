#include "datastructs.h"

int main()
{

    char cmd[10];
    int param;

    while(1) {
        scanf("%s %d", cmd, &param);
        LiveData_Decode(cmd, &param);
    }
}

