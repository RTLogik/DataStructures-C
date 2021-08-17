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
    OK
} LiveData_Status;

typedef enum {
    LIFO = 0,
    LINKED_LIST
} DataStructure_Type;

struct DataStructure
{
    DataStructure_Type type;
    char               name[10];
    union info {
        LIFO_t;
    };
    uint8_t isFree;
};

struct LiveData_Config
{
    uint8_t dataStructsLimit;
};





/************** FUNCTION PROT. **************/
void            ld_decode(char *CMD[]);
LiveData_Status ld_init();
LiveData_Status LIFO_handler(char *CMD[]);
LiveData_Status search_free(struct DataStructure *);
void            log(LiveData_Status);


#endif /* _LIVEDAT_H_ */