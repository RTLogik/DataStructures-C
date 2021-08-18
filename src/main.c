/*
 * main.c by rtlogik
 */

#include "datastructs.h"

#define CMD_LENGTH       60
#define MAX_DATA_STRUCTS 10

void get_command(char *CMD[]);

int main(void)
{
    char cmd1[20], cmd2[20], cmd3[20];
    char *CMD[3] = {cmd1, cmd2, cmd3};

    while(1) {
        
        get_command(CMD);

        if ( strcmp(CMD[0], "exit") == 0 ) 
            exit(0);
        else
            ld_decode(CMD);
    }
}

void get_command(char *CMD[])
{
    char inputCMD[CMD_LENGTH];
    int i = 0;
    size_t slen;

    fgets(inputCMD, CMD_LENGTH, stdin);
    
    char *token = strtok(inputCMD," ");
    while (token != NULL) {
        CMD[i] = token;
        token = strtok(NULL, " ");

        slen = strlen(CMD[i]);
        if (CMD[i][slen] == '\n') 
            CMD[i][slen] = '\0';
        i++;
    }
}