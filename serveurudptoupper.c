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
	int sock,i;
	char buf[20];
	struct sockaddr_in adr_s, adr_c;
	int lg, n;
	/* Création socket */
	sock = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);	
	
	adr_s.sin_family = AF_INET;
	adr_s.sin_addr.s_addr=INADDR_ANY;
	adr_s.sin_port= htons(PORTS);

	/* Attachement socket */
	bind(sock, (struct sockaddr *)&adr_s, sizeof(adr_s));
	for (;;)
	{
		lg = sizeof(adr_c);
		n = recvfrom (sock, buf, 20, 0, (struct sockaddr *)&adr_c, &lg);
		buf[n]=0;
		printf("Chaine reçue %s\n", buf);
		
		for(i=0;i<n;i=i+1)
			buf[i]=(char) ((int)buf[i]-32);	
		
		printf("message to send:%s\n",buf);
		sendto(sock, buf, 20, 0, (const struct sockaddr *)&adr_c,sizeof(adr_c));		
		
	}
	close(sock);
}

