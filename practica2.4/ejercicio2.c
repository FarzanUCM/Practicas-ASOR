#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char** argv)
{	
	int p_h[2];
    int h_p[2];
    
	pipe(p_h);
    pipe(h_p);
    
	pid_t child = fork();

	if(child == 0) //proceso hijo
	{
		char buf[2];
		char message[256];

		int bytes = read(p_h[0], message, 256);
		printf(">> %s", message);
        //write(STDOUT_FILENO, message, bytes);
        sleep(1);
        write(h_p[1], "l\0", 2);

        for(int i = 0; i < 10; i++) {
			message[0] = '\0';
            bytes = read(p_h[0], message, 256);
			printf(">> %s", message);
			//write(STDOUT_FILENO, message, bytes);
			write(h_p[1], "n\0", 2);
        }

		bytes = read(p_h[0], message, 256);
		printf(">> %s", message);
        write(h_p[1], "q\0", 2);

        close(h_p[0]);
        close(h_p[1]);
        close(p_h[0]);
        close(p_h[1]);

	}
	else if(child != -1) //proceso padre
	{
		char buf[2];
		char message[256];

		fgets(message, 256, stdin);
		write(p_h[1], message, strlen(message));

		read(h_p[0], buf, 2); // esperando a que el hijo escriba 'l'

		if(!strcmp(buf, "l"))
		{
			buf[0] = '\0';
			int s = strcmp(buf, "q");
			while (s != 0)
			{	
				message[0] = '\0';
				fgets(message, 256, stdin);				
				write(p_h[1], message, strlen(message));
				read(h_p[0], buf, 2);
				s = strcmp(buf, "q");
			}
		}

        close(h_p[0]);
        close(h_p[1]);
        close(p_h[0]);
        close(p_h[1]);
	}
	else
	{
		perror("Error en fork: ");
		return -1;
	}

	return 0;
}

