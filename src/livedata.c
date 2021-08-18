/*
 * livedata.h by rtlogik
 */

#include "datastructs.h"

#define LIFO_LENGTH 10

LIFO_t lbuf;

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
    printf("%s", CMD[1]);
    if ( strcmp(CMD[1], "init") == 0 ) {    // Initialization

        if ( strcmp(CMD[2], "1") == 0 )
            lbuf.width = 1;
        else if ( strcmp(CMD[2], "2") == 0 )
            lbuf.width = 2;
        else if ( strcmp(CMD[1], "4") == 0 )
            lbuf.width = 4;
        else 
            log(WIDTH_ERROR);

        lbuf.length = LIFO_LENGTH;
        LIFO_Init(&lbuf);

    } else if ( strcmp(CMD[1], "push") == 0 ) {
        int item2push = atoi(CMD[2]);
        printf("Pusheando: %d\n", item2push);
        LIFO_Status status = LIFO_Push(&lbuf, item2push);
        // log(status)
    } else if ( strcmp(CMD[1], "pop") == 0 ) {
        int item2pop;
        LIFO_Status status = LIFO_Pop(&lbuf, &item2pop);
        printf("%d\n", item2pop);
        // log(status)
    } else log(INCORRECT_CMD);

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
    case WIDTH_ERROR:
        printf("Introduce un ancho correcto\n");
        break;

    default:
        break;
    }
  
}