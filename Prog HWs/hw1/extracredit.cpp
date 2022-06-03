#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
using namespace std;

int main(int argc, char *argv[])
{
    int s = atoi(argv[1]);
    if (s < 0) 
    {
        cerr << "Negative sleep time" << std::endl;
        exit(1);
    }
    if (argc < 3)
    {
        cerr << "Missing command" << std::endl;
        exit(1);
    }

    if (strchr(argv[2], '/'))
    {
        std::cerr << "Do not use '/' in path name" << std::endl;
        exit(1);
    }

    char* home = getenv("HOME");
    char envpHome[strlen(home) + 10];
    strcpy(envpHome, "HOME=");
    strcat(envpHome, home);
   
    char* path = getenv("PATH");
    char envpPath[strlen(path) + 10];
    strcpy(envpPath, "PATH=");
    strcat(envpPath, path);

    char* envp[] =
    {
        envpHome,
        envpPath,
        NULL
    };

    int pid = fork();

    if (pid < 0) 
    {
        cerr << "fork failed\n";
        exit(1);
    }
    else if (pid == 0)
    {
        int execargc = argc - 2;
        char* execargv[execargc + 1];

        for (int i = 0; i < execargc; i++)
            execargv[i] = strdup(argv[2+i]);

        execargv[execargc] = NULL;

        execve(execargv[0], execargv, envp);
    }
    else
    {
        sleep(s);

        kill(pid, SIGTERM);

        wait(NULL);
    }

    return 0;
}