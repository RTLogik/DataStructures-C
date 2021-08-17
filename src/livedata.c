/*
 * livedata.h by rtlogik
 */

#include "datastructs.h"

extern struct LiveData_Config ld_config;
extern struct DataStructure *dataStr[];

void ld_decode(char *CMD[])
{
    if ( strcmp(CMD[0], "lifo") == 0 ) {
        LIFO_handler(CMD);

    } else if ( strcmp(CMD[0], "linked") == 0 ) {
        log(STDERROR);
    } else if ( strcmp(CMD[0], "\n") == 0 ) {
        log(NO_COMMAND);
    } else {
        log(INCORRECT_CMD);
    }
}

LiveData_Status LIFO_handler(char *CMD[])
{
    if ( strcmp(CMD[1], "init") == 0 ) {
        uint8_t index = search_free(dataStr);
        if (index = -1) {
            return NO_AVAILABLE;
        } else {
            
        }
    }

}

LiveData_Status ld_init(void)
{
    
    
    
    /* Allocate memory for 10 pointer to DataStructure and free all data structures */
    for (int i = 0; i < 10; i++) {
        dataStr[i] = malloc(size(dataStr));
        dataStr[i]->isFree = 1;
    }
}

LiveData_Status search_free(struct DataStructure *dataStr)
{
    printf("Buscando libre");
}

void log(LiveData_Status status)
{
    switch (status) {
    case NO_COMMAND:
        printf("Introduce un comando!\n");
        break;
    case INCORRECT_CMD:
        printf("Comando incorrecto!\n");
        break;
    
    case STDERROR:
        printf("Ha ocurrido un error\n");
        break;

    default:
        break;
    }
  
}