#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main() {
   printf("Max number of arguments: %ld\n", sysconf(_SC_ARG_MAX));
   printf("Max number of child processes: %ld\n", sysconf(_SC_CHILD_MAX));
   printf("Max number of files: %ld\n", sysconf(_SC_OPEN_MAX));
   return 0;
} 
