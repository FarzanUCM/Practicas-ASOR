#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main() {
   const char* curfile = "/home/usuario_vms/PracticaRobert/ejercicio7.c";
   printf("Max number of links: %ld\n", pathconf(curfile, _PC_LINK_MAX));
   printf("Max length of a filename: %ld\n", pathconf(curfile, _PC_NAME_MAX));
   printf("Max length of a path: %ld\n", pathconf(curfile, _PC_PATH_MAX));
   return 0;
} 
