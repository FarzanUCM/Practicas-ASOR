#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netdb.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <string.h>

int main(int argc, char **argv)
{
	struct addrinfo hints;
	struct addrinfo *result;
	struct sockaddr_storage peer_addr;
	socklen_t peerlen = sizeof(struct sockaddr_storage);

	if (argc < 4) {
		fprintf(stderr, "El programa necesita la dirección, puerto y comando como argumentos.\n");
		exit(EXIT_FAILURE);
	}

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
	hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
	hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */

	int s = getaddrinfo(argv[1], argv[2], &hints, &result);
	
	if (s != 0) 
	{
		fprintf(stderr, "getaddrinfo(): %s\n", gai_strerror(s));
		exit(EXIT_FAILURE);
    }

	int sd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

	connect(sd, result->ai_addr, result->ai_addrlen);

	char buf[128], host[NI_MAXHOST], serv[NI_MAXSERV];

	strcat(argv[3], "\n");
	sendto(sd, argv[3], strlen(argv[3])*sizeof(char), 0, NULL, peerlen);

	int bytes = recvfrom(sd, buf, 128, 0, (struct sockaddr *) &peer_addr, &peerlen);
	buf[bytes] = '\0';

	getnameinfo((struct sockaddr *) &peer_addr, peerlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);

	printf("Respuesta de %s:%s\n\t> %s\n", host, serv, buf);

	return 0;
}
