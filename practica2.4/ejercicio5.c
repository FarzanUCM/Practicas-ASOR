#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/select.h>


int main(int argc, char* argv[]) {
    
    mkfifo("tuberia2", 0666);

	int fd1 = open("tuberia", O_RDONLY | O_NONBLOCK);
    int fd2 = open("tuberia2", O_RDONLY | O_NONBLOCK);
    char buf[256];

    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(fd1, &readfds); 
    FD_SET(fd2, &readfds);

	int maxfd = (fd1 > fd2) ? fd1 : fd2;

	if(select(maxfd+1, &readfds, NULL, NULL, NULL)) //se bloquea hasta que detecta un cambio
	{
		if (FD_ISSET(fd1, &readfds)) {
			int bytes = read(fd1, buf, 255);
			if (bytes == 0) {
				close(fd1);
				fd1 = open("tuberia", O_RDONLY | O_NONBLOCK);
			}
			else
			{ 
				buf[bytes] = '\0';
				printf("Pipeline seleccionado: tuberia\nMensaje: %s---------\n", buf);
			}
		}
		if (FD_ISSET(fd2, &readfds)) {
			int bytes = read(fd2, buf, 255);
			if (bytes == 0) {
				close(fd2);
				fd2 = open("tuberia2", O_RDONLY | O_NONBLOCK);
			}
			else 
			{
				buf[bytes] = '\0';
				printf("Pipeline seleccionado: tuberia2\nMensaje: %s---------\n", buf);
			}
		}
	}
		
}
