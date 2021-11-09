#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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

    if(dup2(r, 2) == -1 || dup2(r, 1) == -1)
    {
	perror("Error en dup2: ");
	return -1;
    }
    else
    {
	fprintf(stderr, "Fallo en el archivo\n");
	fprintf(stderr, "Fallo en la duplicación\n");
        fprintf(stdout, "Creación del archivo con éxito\n");
	fprintf(stdout, "Duplicación del descriptor de fichero con éxito\n");
    }

    return 0;
} 
