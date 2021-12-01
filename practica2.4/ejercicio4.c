#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
	if(argc == 1)
	{
		fprintf(stderr, "El programa debe tener al menos un argumento.\n");
		return -1;
	}

	if(mkfifo("tuberia", 0666) == -1){
		perror("Error creación de tubería: ");
		return -1;
	}

	int fd = open("tuberia", O_WRONLY);
	write(fd, argv[1], (strlen(argv[1])*sizeof(char)) + 1);
}
