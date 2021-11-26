#include <stdio.h>
#include <stdlib.h>


int main(int argc, char** argv)
{
	if(argc == 2)
	{
		system(argv[1]);
		printf("El comando terminó de ejecutarse\n");
		return 0;
	}

	return -1;
}
