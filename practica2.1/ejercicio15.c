#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main() 
{	
     char* outstr = (char *)malloc(200);
     time_t t = time(NULL);
     struct tm* local = localtime(&t);

     if(strftime(outstr, 200, "%A, %d of %B of %Y, %R", local) == 0) 
     {
         fprintf(stderr, "strftime returned 0\n");
         exit(EXIT_FAILURE);
     }

     printf("%s\n", outstr);
     free(outstr);
     return 0;
} 
