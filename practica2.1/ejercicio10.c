#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <pwd.h>
#include <sys/types.h>

int main() {
 
  uid_t ruid = getuid();
  printf("Real UID: %d\n", ruid);
  printf("Effective UID: %d\n", geteuid());

  struct passwd * p= getpwuid(ruid);
  printf("Username: %s\n", p->pw_name);
  printf("Description: %s\n", p->pw_gecos);
  printf("Home directory: %s\n", p->pw_dir);
 
  return 0;
} 
