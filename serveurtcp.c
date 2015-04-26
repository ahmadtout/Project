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
	int sock,nsock,pid;
	char buf[20];
	struct sockaddr_in adr_s, adr_c;
	int lg, n;
	/* Création socket */
	sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);	
	
	adr_s.sin_family = AF_INET;
	adr_s.sin_addr.s_addr=INADDR_ANY;
	adr_s.sin_port= htons(PORTS);

	/* Attachement socket */
	bind(sock, (struct sockaddr *)&adr_s, sizeof(adr_s));
	listen(sock,10); // permet d'accepter 10 clients au Max
	for (;;)
	{
		lg = sizeof(adr_c);
		nsock = accept (sock, (struct sockaddr*)&adr_c, &lg);
		pid=fork();
		if(pid==0)
		{
			close(sock);
			n = read (nsock, buf, 20);
			buf[n]=0;
			printf("Chaine reçue %s\n", buf);
			close(nsock);
			exit(0);
		}
	}
	close(sock);
}

