#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main() {
   int s = setuid(0);
   int errnumber = errno;
   if(s == -1) {
	perror("Error setuid(2)");
	char* errname = strerror(errnumber);

	printf("Error code: %d\n", errnumber);
	printf("Error name: %s\n", errname);
	return -1;
   }
   return 0;
}
