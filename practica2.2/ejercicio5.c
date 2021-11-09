#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char **argv)
{
    int r = open("ejercicio5.txt", O_RDWR | O_CREAT | O_TRUNC, 0645);
    
    if (r == -1)
    {
	perror("Error en la creación del archivo: ");
    	return -1;
    }

    return 0;
}
