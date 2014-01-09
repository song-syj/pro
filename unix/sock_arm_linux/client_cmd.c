#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sock_core.h"

void client_str(FILE *fp, int fd);

int
main(int argc, char *argv[])
{
    int	sockfd;
	struct sockaddr_in servaddr;
	
	if (argc != 2) {
		fputs("usage: tcpcli <IPaddress>\n",stdout);
	}
	sockfd=create_sock(AF_INET, SOCK_STREAM,IPPROTO_TCP);
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
	
	connect_sock(sockfd, (SA *) &servaddr, sizeof(servaddr));
	client_str(stdin,sockfd);
	printf("client_cmd exit normally!\n");
	return 0;
}

void
client_str(FILE *fp, int fd)
{
	char    sendline[MAXLINE], recvline[MAXLINE];
	int n;

	printf("\n\n   ****** The remote terminal ******\n");
	printf("\n   start: start data transmission.");
	printf("\n   write: write data to register.");
	printf("\n   reset: reset the service");
	printf("\n   exit : disconnet the server.");
	printf("\n\ncmd>");
	while (fgets(sendline,MAXLINE,fp) != NULL) {
		
		if (write(fd, sendline, strlen(sendline)+1) < 0) {
				perror("write error");
		}
		memset(recvline, 0, MAXLINE);
		if ((n= readstring(fd, recvline, MAXLINE) ) >  0 ) {
			fputs(recvline, stdout);
		}else if (n == 0) {
			printf("server disconneted!\n");
			exit(1);
		}else {
			perror("read error");
 			exit(1);

		}
		printf("cmd>");
	}
	if (ferror(fp)) {
		fputs("fgets error!\n",stdout);
		exit(1);
	}
	
}







