#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/types.h>
#include "sock_core.h"

void parent_check(int signo);
void senddata (int sockfd, char *filename,
		SA *servaddr, const socklen_t servlen);
int
main(int argc, char *argv[])
{
	struct sockaddr_in servaddr;
	socklen_t servlen;
	int sockfd;

	int send_size;
	
	struct itimerval value, ovalue;
	//int i;
	if (argc < 3) {
		fputs("usage: udpcli <IPaddress> <datafilename>\n",stdout);
		exit(1);
	}

	//creant a socket for TCP/IP communication
	sockfd = create_sock(AF_INET, SOCK_STREAM, 0);

//   send_size = SENDBUFFSIZE;
//   if (setsockopt(sockfd, SOL_SOCKET,
//				   SO_SNDBUF, &send_size, sizeof(send_size)) < 0) {
//       perror("set send buffer size");
//		exit(1);
//   }
//
	//set server's port and IP address
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_DATA_PORT);
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
	
	//set timer and regist a signal handler function
	if (signal(SIGALRM, parent_check) == SIG_ERR) {
		perror("regist signal SIGALARM");
	}
	value.it_value.tv_sec = 2;
	value.it_value.tv_usec = 0;
	value.it_interval.tv_sec = 2;
	value.it_interval.tv_usec =0;
	//	setitimer(ITIMER_REAL, &value, &ovalue);
	
	//i = 0;
	servlen = sizeof(servaddr);
//	while (1) {
//		/* sent data to server */
//		if (sendto(sockfd, &i, 4, 0, (SA *)&servaddr, servlen) != 4) {
//			perror("sendto error");
//			exit(1);
//		}
//		sleep(2);
//		i++;
//	}
	
    senddata(sockfd, argv[2], (SA *)&servaddr, servlen);

	return 0;
}
/*Name: parent_check
 *Description: check its parent process' existence.
 *             if parent process is dead,then the
 *             process itself will be killed by itself.
 *Input: a signal number
 *Output: none.
 */
void
parent_check(int signo)
{
	if (getppid() == 1) {
		raise(SIGKILL);
	}
	return ;
}

float
calctimeval(struct timeval start,
            struct timeval end)
{
    float s;
    s = 1000000 * ( end.tv_sec - start.tv_sec ) + end.tv_usec - start.tv_usec;
    s /= 1000000;
    return s;
}

void
senddata (int sockfd, char *filename, SA *servaddr, const socklen_t servlen)
{
    int fd;
    struct timeval start, end;
    float tvs;

    char buff[MAXLINE*32];
    int rlen;
	int leftlen;
    int rsize;

	connect_sock(sockfd, servaddr, servlen);
    fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("read file");
        exit(1);
    }

    printf("send data start.\n");
    gettimeofday(&start, NULL);
    for(rsize = 0; ; ){
        
        rlen = readn(fd, buff, MAXLINE*4);
        if (rlen < 0)  {
            perror("read data file for transmission");
            exit(1);
        } else if(rlen == 0) {
            gettimeofday(&end, NULL);
            tvs = calctimeval(start, end);
            
            printf("send data end.\n");
            printf("send data size: %d bytes\n", rsize);
            printf("cost %fs \n", tvs);
            write(sockfd, buff, 0);
            break;
        }


		if (writen(sockfd, buff, rlen) < 0) {
			perror("send data to socket");
			exit(1);
		}
		rsize += rlen;
    }
    return;
}










