#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/sysmacros.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if(argc == 1)
    {
	fprintf(stderr, "El programa necesita un nombre de fichero como argumento\n");
	return -1;
    }

    char* path = argv[1];
    struct stat statbuf;

    int r = stat(path, &statbuf);

    if(r == -1)
    {
	perror("Error de stat: ");
	return -1;
    }
         
    if(S_ISREG(statbuf.st_mode))
    {
	char * hard = malloc(strlen(argv[1])*sizeof(char) + 6);
	char * sym = malloc(strlen(argv[1])*sizeof(char) + 5);
	strcpy(hard, argv[1]);
	strcpy(sym, argv[1]);
	if(link(argv[1], strcat(hard, ".hard")) == -1)
	{
	    perror("Error al crear enlace rígido");
	    return -1;
	}
	if(symlink(argv[1], strcat(sym, ".sym")) == -1)
	{
	    perror("Error al crear enlace simbólico"); 
	    return -1;
	}
    }
 
    return 0;
} 
