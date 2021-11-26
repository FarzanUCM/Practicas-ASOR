#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char** argv)
{
	if(argc >= 2)
	{
		pid_t f = fork();
		if(f == 0)
		{
			pid_t sid = setsid();

			if(chdir("/tmp") == -1){
				perror("Error cambio de directorio: ");
				return -1;
			}

			int fd1 = open("/tmp/daemon.out", O_CREAT|O_WRONLY|O_TRUNC, 0666);
			int fd2 = open("/tmp/daemon.err", O_CREAT|O_WRONLY|O_TRUNC, 0666);
			int fd0 = open("/dev/null", O_WRONLY);
			dup2(fd1, 1);
			dup2(fd2, 2);
			dup2(fd0, 0);
			execvp(argv[1], argv+1);
		}
		else{
			sleep(10);
			return 0;
		}
	}

	return -1;
}
