#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <time.h>
#include <string.h>

/* Group Members: Adil Bukhari, Niharika Misal, Mihika Krishna*/

char* signames[32] = {
     "Signal 0",     /*  signal 0 -- meaningless */
        "SIGHUP",       /* 1 */
        "SIGINT",
        "SIGQUIT",
        "SIGILL",
        "SIGTRAP",
        "SIGABRT",
        "SIGEMT",
        "SIGFPE",
        "SIGKILL",
        "SIGBUS",       /* 10 */
        "SIGSEGV",
        "SIGSYS",
        "SIGPIPE",
        "SIGALRM",
        "SIGTERM",
        "SIGUSR1",
        "SIGUSR2",
        "SIGCHLD",
        "SIGCONT",
        "SIGTSTP",      /* 20 */
        "SIGTTIN",
        "SIGTTOU",
        "SIGSTOP",
        "SIGXCPU",
        "SIGXFSZ",
        "SIGVTALRM",
        "SIGPROF",
        "SIGWINCH",
        "SIGPOLL",
        "SIGUSR1",      /* 30 */
        "SIGUSR2",
};

void signal_handler(int signum)
{
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char s[64];
    strftime(s, sizeof(s), "%c", tm);
    printf("%s Received signal %d (%s)\n", s, signum, (signames[signum]));

}

int main(int argc, char *argv[])
{
    for (int i=0; i<32; i++)
    {
        signal(i,signal_handler);
    }
    // loop until kill -9 SIGKILL
    while (1) sleep(1); 
}

