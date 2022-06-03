#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>

/* Group Members: Adil Bukhari, Niharika Misal, Mihika Krishna*/

void handler(int sig){
        wait(NULL);
        exit(0);
}
    
int main(int argc, char *argv[])
{

   
    if (argc < 3) 
    {
        printf("%s\n", "Usage: timeout sec command [args ...]");
        exit(1);
    }

    int num_sec = atoi(argv[1]);

    if (num_sec < 0) 
    {
        printf("%d is not a positive integer\n", num_sec);
        exit(1);
    }
    
    int rc = fork();

    if (rc < 0) 
    {
        
        fprintf(stderr, "fork failed\n");
    } 
    else if (rc == 0) 
    {
    
        char* child_args[argc-1];
        int i;
        for (i=2; i<argc; i++) 
        {
            child_args[i-2] = argv[i];
        }

        child_args[argc-2] = NULL;
        extern char** environ;
        int ret = execve(child_args[0], child_args, environ);
        if(ret == -1) perror("execve");
        exit(0);
    } 
    else 
    {   
        signal(SIGCHLD, handler);
        sleep(num_sec);
        kill(rc, SIGTERM);
    }
    exit(0);
    return 0;
}