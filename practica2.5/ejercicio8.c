#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netdb.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

void gestionar(int clisd)
{
	char buf[128];
	int c;

	while (c = recv(clisd, buf, 127, 0)) 
	{
		buf[c] = '\0';
		send(clisd, buf, c + 1, 0);
	}

	printf("Conexión terminada\n");
}

int main(int argc, char **argv)
{
	struct addrinfo hints;
	struct addrinfo *result;
	struct sockaddr_storage peer_addr;
	socklen_t peerlen = sizeof(struct sockaddr_storage);

	if (argc != 3) {
		fprintf(stderr, "El programa necesita la dirección y el puerto como argumentos.\n");
		exit(EXIT_FAILURE);
	}

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
	hints.ai_socktype = SOCK_STREAM; /* Stream socket */
	hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */

	int s = getaddrinfo(argv[1], argv[2], &hints, &result);
	
	if (s != 0) 
	{
		fprintf(stderr, "getaddrinfo(): %s\n", gai_strerror(s));
		exit(EXIT_FAILURE);
    }

	int sd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

	int rc = bind(sd, (struct sockaddr *) result->ai_addr, result->ai_addrlen);

	if(rc != 0)
	{
		perror("bind(): ");
		exit(EXIT_FAILURE);
	}

	listen(sd, 5);

	char host[NI_MAXHOST], serv[NI_MAXSERV];

	while(1)
	{
		int clisd = accept(sd, (struct sockaddr *) &peer_addr, &peerlen);

		pid_t child = fork();

		if(child == 0)
		{
			getnameinfo((struct sockaddr *) &peer_addr, peerlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
			printf("Conexión desde %s:%s\n", host, serv);
			gestionar(clisd);
			exit(0);
		}
		else if(child == -1)
		{
			perror("fork(): ");
			exit(EXIT_FAILURE);
		}
		else
		{
			close(clisd);
		}
	}

	return 0;
}
