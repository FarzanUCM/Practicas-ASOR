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

	if (argc != 3) {
		fprintf(stderr, "El programa necesita la dirección y el puerto como argumentos.\n");
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

	int rc = bind(sd, (struct sockaddr *) result->ai_addr, result->ai_addrlen);

	if(rc != 0)
	{
		perror("bind(): ");
		exit(EXIT_FAILURE);
	}

	char buf[3], host[NI_MAXHOST], serv[NI_MAXSERV];

	while(1)
	{
		int bytes = recvfrom(sd, buf, 2, 0, (struct sockaddr *) &peer_addr, &peerlen);
		buf[bytes] = '\0';

		getnameinfo((struct sockaddr *) &peer_addr, peerlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);

		printf("%d bytes de %s:%s\n", bytes, host, serv);

		if(buf[0] == 't')
		{
			char hour[128];
			time_t t = time(NULL);
			struct tm* gm = gmtime(&t);
			size_t size = strftime(hour, 128, "%H:%M:%S %p", gm);

			if(size != 0) {
				sendto(sd, hour, size, 0, (struct sockaddr *) &peer_addr, peerlen);
			}
		}
		else if(buf[0] == 'd')
		{
			char hour[128];
			time_t t = time(NULL);
			struct tm* gm = gmtime(&t);
			size_t size = strftime(hour, 128, "%d-%m-%Y", gm);

			if(size != 0) {
				sendto(sd, hour, size, 0, (struct sockaddr *) &peer_addr, peerlen);
			}
		}
		else if(buf[0] == 'q')
		{
			printf("Saliendo...\n");
			break;
		}
		else
		{
			printf("Comando %c no soportado\n", buf[0]);
		}

	}

	return 0;
}
