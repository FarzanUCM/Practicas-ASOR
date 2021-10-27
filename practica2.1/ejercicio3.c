#include <stdio.h>
#include <errno.h>

int main() {
	printf("Lista de errores del sistema:\n");
	for(int i=0; i < sys_nerr; i++)
	{
		printf("* Error no.%d: %s\n", i, sys_errlist[i]);
	}

	return 0;
}
