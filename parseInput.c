//takes the input string and parses it into array of string

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <limits.h>
#include "myHeader.h"

char **parseInput(char* input)
{
    int size = 1024;
    char **commands = malloc(size * sizeof(char *));
    if(!commands){
                fprintf(stderr, "PIKA: allocation error\n");
                exit(EXIT_FAILURE);
            }
    char *command ;
    char *breakers = " \t\n\a\r";
    int positionCommands=0;

    command = strtok(input,breakers);
    while(command!=NULL){
        commands[positionCommands++] = command;
        if(positionCommands==size){
            size+=size;
            commands = realloc(commands,size);
            if(!commands){
                fprintf(stderr, "PIKA: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
        command = strtok(NULL,breakers);
    }
    commands[positionCommands] = NULL;

    return commands;
}
