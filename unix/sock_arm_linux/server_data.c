#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/time.h>
#include "sock_core.h"

void recvdata(int sockfd, char *filename);

int
main (int argc, char *argv[])
{
	struct sockaddr_in servaddr, cliaddr;
	//	char data;
	int recv_size =0;
	//	socklen_t clilen;
	int listenfd, connfd;

	int clilen;

	
    if (argc < 2) {
        perror("usage: <filename>");
    }
	listenfd = create_sock(AF_INET, SOCK_STREAM, 0);
    //get the primary size of socket recive buffer.
    //set the size of socket recive buffer
//    recv_size = SENDBUFFSIZE;
//    if (setsockopt(sockfd, SOL_SOCKET,
//				   SO_RCVBUF, &recv_size, sizeof(recv_size)) < 0) {
//        perror("set send buffer size");
//		exit(1);
//    }
//    
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_DATA_PORT);
	bind_sock(listenfd, (SA *)&servaddr, sizeof(servaddr));
    
	//clilen = sizeof(cliaddr);
	listen_sock(listenfd, LISTENQ);
	
	clilen = sizeof(cliaddr);
 again:	
	connfd = accept_sock(listenfd, (SA *)&cliaddr, &clilen);
	if (errno == EINTR)
		goto again;
		
	printf("connecting with client from IP address, %s....\n",
		   inet_ntoa(cliaddr.sin_addr));
	fflush(stdout);

	close (listenfd);
	printf("waiting data received\n");
	
	recvdata(connfd, argv[1]);
    
	return 0;
}


static float
calctimeval(struct timeval start,
            struct timeval end)
{
    float s;
    s = 1000000 * ( end.tv_sec - start.tv_sec ) + end.tv_usec - start.tv_usec;
    s /= 1000000;
    return s;
}

void
recvdata(int sockfd, char *filename)
{
    int fd;
	fd_set rset;
	struct timeval tv;
	struct timeval start, end;
	float tvs;
	
	char buff[MAXLINE*32];
	int rlen;
	int rsize;
	char rflag = 0;

	fd = open(filename, O_WRONLY|O_CREAT|O_TRUNC, 0600);
	if (fd < 0) {
		perror("open recdata file");
		exit(1);
	}
	
	for (rsize = 0; ; ) {
		
		if (rflag == 0) {
			
			rlen = recv(sockfd, buff, 0, MSG_PEEK);
            rflag = 1;
            printf("read data start.\n");
            gettimeofday(&start, NULL);
        } else {
//			int ret;
//			
//			tv.tv_sec = 2;
//			tv.tv_usec = 0;
//			
//			FD_ZERO(&rset);
//			FD_SET(sockfd, &rset);
//			ret = select(sockfd+1, &rset, NULL, NULL, &tv);
//
//			if (ret < 0) {
//				perror("select");
//				exit(1);
//			} else if ( ret == 0) {
//				gettimeofday(&end, NULL);
//				tvs = calctimeval(start, end);
//					
//				printf("read data end.\n");
//				printf("read data size: %d\n", rsize);
//				printf("cost %f second \n", tvs);
//				
//				break;
//			} else {
//			
//				if (FD_ISSET(sockfd, &rset))  {
			rlen = readn(sockfd, buff, MAXLINE*4);
			if (rlen < 0) {
				perror("read socket");
				exit(1);
			}else if (rlen == 0){
				gettimeofday(&end, NULL);
				tvs = calctimeval(start, end);
					
				printf("read data end.\n");
				printf("read data size: %d\n", rsize);
				printf("cost %fs \n", tvs);
				break;

			}
			
			writen(fd, buff, rlen);
			rsize += rlen;
					
		}
	}
}
	
