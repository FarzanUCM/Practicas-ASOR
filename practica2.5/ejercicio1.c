#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char **argv)
{
	if(argc == 1)
	{
		fprintf(stderr, "ERROR: Se necesita el nombre de host como argumento\n");
		return -1;
	}
	
	struct addrinfo *res;
	int rc = getaddrinfo(argv[1], NULL, NULL, &res);
	
	if(rc != 0) {
		perror("Error getaddrinfo(): ");
		return -1;
	}
	
	char host[NI_MAXHOST];
	char serv[NI_MAXSERV];
	
	struct addrinfo* next = res;
	
	while(next != NULL)
	{	
		rc = getnameinfo(next->ai_addr, next->ai_addrlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);
		
		if (rc != 0){
			perror("Error getnameinfo(): ");
			return -1;
		}

		printf("Host: %s\nPort: %s\nFamily: %d\nSocktype: %d\n", host, serv, next->ai_family, next->ai_socktype);
		printf("-----------\n");
		
		host[0] = '\0';
		serv[0] = '\0';

		next = next->ai_next;
	}

	return 0;
}
