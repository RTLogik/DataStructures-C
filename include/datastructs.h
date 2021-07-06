/*
 * datastructs.h
 * by rtlogik
 */

#ifndef _DATASTRUCTS_H_
#define _DATASTRUCTS_H_

#include <stdint.h>
#include <stdio.h>

#include "lifo.h"
#include "livedata.h"

typedef union {
    LIFO_Status LIFO;
} DataStructs_Status;


#endif /* _DATASTRUCTS_H_ */