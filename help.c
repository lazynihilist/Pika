#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <limits.h>
#include "myHeader.h"

void help(void){
    printf("*******************************************\n");
    printf("*                                         * \n");
    printf("* This is Sakib's Implementation of Shell *\n");
    printf("*                                         * \n");
    printf("*******************************************\n\n\n\n");

    printf("The built-in functions are:\n");
    printf("1.echo\n2.pwd\n3.cd\n4.help\n5.exit\n\n");

    printf("Features:\n1.I/O Redirection\n2.Pipe\n3.Background Process\n");

}