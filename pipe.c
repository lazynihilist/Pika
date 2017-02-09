//implements pipeline and I/O redirection

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <limits.h>
#include "myHeader.h"

void pipelining(char **commands){
    int size = 100;
    int fd[2];  //for creating pipe
    int position = 0;
    int in = 0;
    int out = 1;
    int wa = 0; //indicates if a process should be run in background or foreground
    char **output = malloc(100 * sizeof(char *));   //temporary string array for execution
    if(!output){
    fprintf(stderr, "PIKA: allocation error\n");
    exit(EXIT_FAILURE);
    }

    while(*commands){
        if(position==1023) {
            size += 100;
            output = realloc(output,size * sizeof(char *));
            if(!output){
                fprintf(stderr, "PIKA: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
        wa = 0;

        //if there is a pipe
        if(!strcmp(*commands,"|")) {
            output[position] = NULL;
            pipe(fd);
            execute(output,in,fd[1],0);
            close(fd[1]);
            in = fd[0];
            position = 0;
        }

        //if there is a output redirection or output append redirection
        else if(!strcmp(*commands,">")) {
            output[position] = NULL;
            *commands++;
            if(!strcmp(*commands,">")){
                *commands++;
                out = open(*commands,O_WRONLY | O_APPEND | O_CREAT,S_IRUSR | S_IWUSR);
            }
            else out = open(*commands,O_WRONLY | O_TRUNC | O_CREAT,S_IRUSR | S_IWUSR);
            if(!strcmp(++*commands,"&")) wa = 1;
            break;
        }

        //if there is a input redirection
        else if(!strcmp(*commands,"<")) {
            output[position] = NULL;
            *commands++;
            in = open(*commands,O_RDONLY,S_IRUSR | S_IWUSR);
            continue;
        }

        //checks if the process should be run in background
        else if(!strcmp(*commands,"&")){
            wa = 1;
            break;
        }

        //otherwise takes the string into the temporarystring array
        else output[position++] = *commands;
        *commands++;
    }

    //for coloring the output
    if(!strcmp(output[0],"ls") || !strcmp(output[0],"grep")){
            output[position++] = "--color";
    }

    output[position] = NULL;
    execute(output,in,out,wa);

    //closes the fds
    if(in!=0) close(in);
    if(out!=1) close(out);
    free(output);
    return ;
}
