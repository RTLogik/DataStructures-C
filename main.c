#include "osiris.h"

int main()
{

    char cmd[10];
    int param;

    while(1) {
        scanf("%s %d", cmd, &param);
        LiveDat_Decode(cmd, &param);
    }
}

