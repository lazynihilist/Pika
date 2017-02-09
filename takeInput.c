#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <limits.h>
#include "myHeader.h"

char *takeInput(void)
{
    int size = 1024;
    char *line = malloc(size * sizeof(char));
    if (!line) {
        fprintf(stderr, "PIKA: memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    int position = 0;

    int c;

    while(1)
    {
        c = getchar();

        if(c==EOF || c=='\n') {
            line[position] = '\0';
            break;
        }

        //special case when there is no space between pipe or I/O redirection
        else{
            if(c=='|' || c=='>' || c=='<') line[position++] = ' ';
            line[position++] = c ;
            if(c=='|' || c=='>' || c=='<') line[position++] = ' ';
        }

        if(position==size-3)
        {
            size += size;
            line = realloc(line,size * sizeof(char));
            if(!line){
                fprintf(stderr, "PIKA: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    return line;
}
