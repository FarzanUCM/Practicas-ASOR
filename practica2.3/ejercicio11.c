#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int main() 
{
    setenv("SLEEP_SECS", "15", 1);
    sigset_t set;
    
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGTSTP);
    sigprocmask(SIG_BLOCK, &set, NULL);

    int secs = atoi(getenv("SLEEP_SECS"));
    sleep(secs);
    
    sigset_t pending;
    
    sigpending(&pending);
    if (sigismember(&pending, SIGINT))
        printf("Recibida SIGINT\n");
    if (sigismember(&pending, SIGTSTP))
        printf("Recibida SIGSTP\n");
    
    sigprocmask(SIG_UNBLOCK, &set, NULL);
    
    printf("Señales desbloqueadas\n");

    return 0;
}
