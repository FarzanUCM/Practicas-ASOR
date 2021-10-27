#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>

int main() {
 
  printf("Real UID: %d\n", getuid());
  printf("Effective UID: %d\n", geteuid());
  return 0;
} 
