#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv)
{
	if(argc >= 2)
	{
		execvp(argv[1], argv+1);
		printf("El comando terminó de ejecutarse\n");
		return 0;
	}

	return -1;
}
