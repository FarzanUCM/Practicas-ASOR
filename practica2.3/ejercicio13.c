#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

volatile int detener = 0;

void handler(int signal) {
    if (signal == SIGUSR1){
        detener = 1;
    }
}

int main(int argc, char** argv) 
{
    if (argc == 2) {
        struct sigaction sa;
        sigset_t set;
    
        sigemptyset(&set);

        sa.sa_handler = (void *) handler;
        sigaction(SIGUSR1, &sa, NULL);
        sigaction(SIGALRM, &sa, NULL);

        alarm(atoi(argv[1]));
        
        sigsuspend(&set);
        
        if(!detener) 
        {
            unlink(argv[0]);
            printf("Ejecutable borrado\n");
        }
        else {
            printf("Borrado detenido por usuario\n");
        }

        return 0;
    }

    return -1;
}
