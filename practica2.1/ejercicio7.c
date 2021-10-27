#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main() {
   printf("Max number of links: %ld\n", pathconf("/bin/bash", _PC_LINK_MAX));
   printf("Max length of a filename: %ld\n", pathconf("/bin/bash", _PC_NAME_MAX));
   printf("Max length of a path: %ld\n", pathconf("/bin/bash", _PC_PATH_MAX));
   return 0;
} 
