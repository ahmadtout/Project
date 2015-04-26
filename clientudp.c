#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define PORTS 2058
main(int argc, char ** argv)
{
	struct hostent *h;
	struct sockaddr_in adr_s,adr_c;
	char buf[20];
	int sock;
	/* création socket */
	sock = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	
	/* Construction adresse local */
	adr_c.sin_family = AF_INET;
	adr_c.sin_addr.s_addr=INADDR_ANY;
	adr_c.sin_port= htons(PORTS);

	/* Attachement socket */
	bind(sock, (struct sockaddr *)&adr_c, sizeof(adr_c));

	/* Construction adresse du serveur */
	h=gethostbyname("localhost");	
	adr_s.sin_family = AF_INET;
	bcopy((char *)h->h_addr, 
       		(char *)&adr_s.sin_addr,
        	h->h_length);	
	adr_s.sin_port= htons(PORTS);

	printf("name=?\n");
	scanf("%s",buf);
	sendto(sock, buf, 20, 0, (const struct sockaddr *)&adr_s,sizeof(adr_s));
	close (sock);
}
