#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

int main(int argc, char** argv)
{
	int fd[2];

	if(pipe(fd) == -1){
		perror("Error en creación del pipe: ");
		return -1;
	}

	int child = fork();

	if(child == 0) //proceso hijo
	{
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		execvp(argv[3], argv + 3);

	}
	else if(child != -1) //proceso padre
	{
		char* argv_child[3] = {argv[1], argv[2], NULL};
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		execvp(argv[1], argv_child);

	}
	else
	{
		perror("Error en fork: ");
		return -1;
	}

	return 0;
}

