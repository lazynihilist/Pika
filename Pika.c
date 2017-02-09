#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <limits.h>
#include "myHeader.h"

int main(int argc,char **argv)
{
    welcome();
	char *input;
	char **commands;

    while(1){
    //Prints the current directory
    printf("<PIKA>    %s>",getcwd(NULL,PATH_MAX+1));
    input = takeInput();
    if(input[0]=='\0') continue; // continues if the user enters "\n"
    commands =parseInput(input);
    pipelining(commands);
    free(input);
    free(commands);
    }

    return 0;
}
