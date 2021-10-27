#include <stdio.h>
#include <time.h>

int main() 
{	
     time_t t = time(NULL);
     struct tm* local = localtime(&t);
     printf("Current year: %d\n", local->tm_year + 1900); //la documentacion dice que tm_year devuelve el año menos 1900
     return 0;
} 
