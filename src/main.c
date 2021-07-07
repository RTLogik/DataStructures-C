/*
 * main.c by rtlogik
 */

#include "datastructs.h"

#define CMD_LENGTH 60

void get_command(char *CMD[]);

int main(void)
{
    char cmd1[20], cmd2[20], cmd3[20];
    char *CMD[3] = {cmd1, cmd2, cmd3};

    while(1) {
        
        get_command(CMD);

        if ( strcmp(CMD[0], "exit") == 0 ) 
            exit(0);
        //else
            //LiveData_Decode(cmd);
    }
}

void get_command(char *CMD[])
{
    char InputCMD[CMD_LENGTH];
    int i = 0;
    size_t slen;

    fgets(InputCMD, CMD_LENGTH, stdin);
    
    char *token = strtok(InputCMD," ");
    while (token != NULL) {
        CMD[i] = token;
        token = strtok(NULL, " ");

        slen = strlen(CMD[i]);
        if (CMD[i][slen-1] == '\n') 
            CMD[i][slen-1] = '\0';
        i++;
    }

    
    printf("CMD1: %s\nCMD2: %s\nCMD3: %s\n", CMD[0], CMD[1], CMD[2]);

}