#include <stdio.h>
#include <errno.h>
#include <sys/utsname.h>

int main() {
   struct utsname buf;
   int e = uname(&buf);
   
   if(e == -1) {
	perror("Error uname(2)");
	return -1;
   }
   
   printf("OS Name: %s\n", buf.sysname);
   printf("Node Name: %s\n", buf.nodename);
   printf("OS Release: %s\n", buf.release);
   printf("OS Version: %s\n", buf.version);
   printf("Machine ID: %s\n", buf.machine); 
   return 0;
}
