/*
 * livedata.h by rtlogik
 */

#include "datastructs.h"

DataStructs_Status LiveData_Decode(char *CMD1, char *CMD2, char *CMD3)
{

    if (strcmp(CMD2, "pene") == 0) {
        printf("Exito!\n");
    } else {
        printf("Vaya...\n");
    }

}