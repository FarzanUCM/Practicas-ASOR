#include <time.h>
#include <stdio.h>
#include <sys/time.h>

int main() 
{
   struct timeval tv1;
   struct timeval tv2;
   int m = 0;
   
   gettimeofday(&tv1, NULL);

   for(int i = 0; i < 1000000; i++)
   {
	m++;
   }

   gettimeofday(&tv2, NULL);
   printf("Time (in microseconds): %ld\n", tv2.tv_usec - tv1.tv_usec);     

   return 0;
} 
