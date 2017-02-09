#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <limits.h>
#include "myHeader.h"

void builtIn(char **command,int in,int out){
    if(!strcmp(command[0],"pwd")){
            printf("%s\n",getcwd(NULL,PATH_MAX +1));
    }

    else if(!strcmp(command[0],"echo")){
        *command++;
        while(*command){
            printf("%s ",*command++);
        }
        printf("\n");
    }

    else if(!strcmp(command[0],"cd")){
        int errno = chdir(command[1]);
        if(errno) perror("PIKA:");
    }

    else if(!strcmp(command[0],"exit")){
        printf("\n\n******************************************\n\n");
        exit(EXIT_SUCCESS);
    }

    else help();
}
