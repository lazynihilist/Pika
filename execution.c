//executes the string

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <limits.h>
#include "myHeader.h"

void execute(char **commands,int in,int out,int wa){
    int state = 1;  //keeps track if a task is done by builtin functions
    int status;
    char *builtIns[]={"cd","echo","pwd","exit","help",0};
    int i=0;


    //checks if it's a builtin function if yes then calls builtin function
    while(builtIns[i]){
        if(!strcmp(commands[0],builtIns[i++])) {
            builtIn(commands,in,out);
            state = 0;
            break;
        }
    }

    //executes if not a builtin function
    if(state){
        pid_t pid = fork();
        if(pid==0){

            //if I/O redirection is present then duplicates and closes the unused file descriptors
            if(in!=0){
                dup2(in,0);
                close(in);
            }
            if(out!=1){
                dup2(out,1);
                close(out);
            }

            //for daemon
            if(wa){
                pid_t pid2,sid;
                pid2 = fork();
                if(pid2<0) printf("Error in forking\n");

                //daemon child process that executes the work
                else if(pid2==0){
                    execvp(commands[0],commands);
                    perror("PIKA:");
                    _exit(1);
                }

                //daemon that closes all the links with the daemon child
                else{
                    sid = setsid();
                    if (sid < 0) {
                    _exit(EXIT_FAILURE);
                    }
                    close(STDIN_FILENO);
                    close(STDOUT_FILENO);
                    close(STDERR_FILENO);
                }

            }

            //for foreground
            else{
                execvp(commands[0],commands);
                perror("PIKA:");
                _exit(1);
            }
        }

        else if(pid<0) printf("Error forking\n");

        //parent process that either waits or returns to main process
        else {
            if(!wa) waitpid(pid,&status,0);
            else {
                printf("%d  started.\n",pid);
            }
        }
    }
    return ;
}
