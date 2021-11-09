#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

int main(int argc, char **argv)
{
    if(argc == 1)
    {
	fprintf(stderr, "El programa necesita un nombre de fichero como argumento\n");
	return -1;
    }
    
    int r = open(argv[1], O_RDWR | O_CREAT, 0666);

    if(r == -1)
    {
 	perror("Error al abrir el archivo: ");
    	return -1;
    }

    int lock = lockf(r, F_TLOCK, 0);
    
    if(lock != -1) //si está desbloqueado
    {
	char hora[200];
	time_t t = time(NULL);
     	struct tm* local = localtime(&t);
        strftime(hora, 200, "%H:%M:%S", local);	
    	printf("Cerrojo bloqueado a las: %s\n", hora);
	
	sleep(30);
	
	lockf(r, F_ULOCK, 0);
	printf("Cerrojo desbloqueado\n");
    } 

    return 0;
} 
