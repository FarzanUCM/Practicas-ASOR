#include <stdio.h>
#include <signal.h>

volatile int cont_stop = 0;
volatile int cont_int = 0;

void handler(int signal)
{
    if(signal == SIGTSTP)
        cont_stop++;
    else if(signal == SIGINT)
        cont_int++;
}

int main() 
{
    struct sigaction sa;
    sa.sa_handler = (void *) handler;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTSTP, &sa, NULL);
    while (cont_stop + cont_int < 10);

    printf("Num. SIGTSTP: %d\n", cont_stop);
    printf("Num. SIGINT: %d\n", cont_int);

    return 0;
}
