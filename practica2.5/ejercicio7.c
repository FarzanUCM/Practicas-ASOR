#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netdb.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	struct addrinfo hints;
	struct addrinfo *result;

	if (argc < 3) {
		fprintf(stderr, "El programa necesita la dirección y puerto como argumentos.\n");
		exit(EXIT_FAILURE);
	}

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
	hints.ai_socktype = SOCK_STREAM; /* Datagram socket */
	hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */

	int s = getaddrinfo(argv[1], argv[2], &hints, &result);
	
	if (s != 0) 
	{
		fprintf(stderr, "getaddrinfo(): %s\n", gai_strerror(s));
		exit(EXIT_FAILURE);
    }

	int sd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

	connect(sd, (struct sockaddr *)result->ai_addr, result->ai_addrlen);
	
	char buf[128], rec[128], host[NI_MAXHOST], serv[NI_MAXSERV];

	while(1)
	{
		fgets(buf, 128, stdin);
		send(sd, buf, strlen(buf), 0);

		if(strcmp(buf, "Q\n") == 0)
		{
			close(sd);
			break;
		}
		else {
			recv(sd, rec, 127, 0);
			printf("Recibido: %s", rec);
		}

	}

	return 0;
}
