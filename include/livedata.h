/*
 * livedata.h by rtlogik
 */

#ifndef _LIVEDAT_H_
#define _LIVEDAT_H_


typedef enum {
    NO_COMMAND = 0,
    INCORRECT_CMD,
    LIFO_ERROR,
    NO_AVAILABLE,
    STDERROR,
    WIDTH_ERROR,
    OK
} LiveData_Status;


/************** FUNCTION PROT. **************/
void            ld_decode(char *CMD[]);
LiveData_Status LIFO_handler(char *CMD[]);
void            log(LiveData_Status);


#endif /* _LIVEDAT_H_ */