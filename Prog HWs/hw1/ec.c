#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>


int main(int argc, char *argv[])
{
    int num_sec = atoi(argv[1]);

    if (num_sec < 0) 
    {
        printf("%s\n", "Negative sleep time");
    }
    if (argc < 3) 
    {
        printf("%s\n", "Missing command");
    }

    int rc = fork();

    if (rc < 0) 
    {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
    } 
    else if (rc == 0) 
    {
    // child (new process)
        char* child_args[argc-1];
        for (int i=2; i<argc; i++) 
        {
            child_args[i-2] = argv[i];
        }
        child_args[argc-2] = NULL;
        execvp(child_args[0], child_args);
    } 
    else 
    {
        // parent goes down this path (original process)
        sleep(num_sec);
        kill(rc, SIGTERM);
    }
    exit(1);
    return 0;
}