#include "sock_core.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


int
create_sock(int family, int type, int protol)
{
	int listenfd;
	listenfd = socket(family, type, protol);
	if (listenfd < 0) {
		perror("create  socket");
		exit(1);
	}
		
	return listenfd;
}

void
bind_sock(int fd, const struct sockaddr *sa, socklen_t len)
{
	if (bind(fd, sa, len) < 0) {
		perror("bind socket");
		exit(1);
	}
	return ;
}
void
listen_sock(int sockfd, int backlog )
{
	if (listen (sockfd, backlog)) {
		perror("listen socket");
		exit(1);
	}
	return;
}	

int
accept_sock(int sockfd, const struct sockaddr *cliaddr, socklen_t *len)
{
	int clifd;
	clifd = accept(sockfd, cliaddr, len);
	if (clifd < 0 && errno != EINTR) {
		perror("accept");
	}
	return clifd;
}


void
connect_sock(int sockfd,const struct sockaddr *servaddr, socklen_t len)
{
	if (connect(sockfd, servaddr, len) < 0) {
		perror("connet socket");
		exit(0);
	}
	return;
}

ssize_t
readline(int fd, void *vptr, size_t maxlen)
{
	ssize_t	n, rc;
	char	c, *ptr;

	ptr = vptr;
	for (n = 1; n < maxlen; n++) {
		if ( (rc = read(fd, &c, 1)) == 1) {
			*ptr++ = c;
			if (c == '\n')
				break;
		} else if (rc == 0) {
			if (n == 1)
				return(0);	/* EOF, no data read */
			else
				break;		/* EOF, some data was read */
		} else
			return(-1);	/* error */
	}

	*ptr = 0;
	return(n);
}
/*
 *Name: readstring
 *Description: read a string from socket, if read a maxlen - 1 bytes and  still can't meet '\0'
 *             then add '\0' at the end return the maxlen - 1 ;else return the length of string include '\0'
 *             character.
 *Input : fd, a files descriptor;
 *        vptr, a ponitor that points a space holding read string.
 *        maxlen, maxsize the space holding read string.
 * Return : the size bytes read from fd.
 */
ssize_t
readstring(int fd, void *vptr, size_t maxlen)
{
	ssize_t	n, rc;
	char	c, *ptr;

	ptr = vptr;
	for (n = 1; n < maxlen; n++) {
again:
		if ( (rc = read(fd, &c, 1)) == 1) {
			*ptr++ = c;
			if (c == '\0')
				return n;
		} else if (rc == 0) {     /* EOF, some data was read */
			*ptr = 0;
			return (n-1);
		} else {		          /* some error */
			if (errno == EINTR) { /* caused by signal */
				goto again;
			}
			else {
				perror("readstring");	      /* error */
				exit(1);
			}
		}
	}
	/* read maxlen-1 and can't read '\0' */
	*ptr = '\0';
	return (n - 1);
}

ssize_t						/* Read "n" bytes from a descriptor. */
readn(int fd, void *vptr, size_t n)
{
	size_t	nleft;
	ssize_t	nread;
	char	*ptr;

	ptr = vptr;
	nleft = n;
	while (nleft > 0) {
		if ( (nread = read(fd, ptr, nleft)) < 0) {
			if (errno == EINTR)
				nread = 0;		/* and call read() again */
			else
				return(-1);
		} else if (nread == 0)
			break;				/* EOF */

		nleft -= nread;
		ptr   += nread;
	}
	return(n - nleft);		/* return >= 0 */
}
/* end readn */

ssize_t						/* Write "n" bytes to a descriptor. */
writen(int fd, const void *vptr, size_t n)
{
	size_t		nleft;
	ssize_t		nwritten;
	const char	*ptr;

	ptr = vptr;
	nleft = n;
	while (nleft > 0) {
		if ( (nwritten = write(fd, ptr, nleft)) <= 0) {
			if (nwritten < 0 && errno == EINTR)
				nwritten = 0;		/* and call write() again */
			else
				return(-1);			/* error */
		}

		nleft -= nwritten;
		ptr   += nwritten;
	}
	return(n);
}
/* end writen */

ssize_t						/* Read "n" bytes from a descriptor. */
recvfromn(int fd, void *vptr, size_t n,
          int flags,
          struct sockaddr *souraddr,
          socklen_t *sourlen)
{
	size_t	nleft;
	ssize_t	nread;
	char	*ptr;

	ptr = vptr;
	nleft = n;
	while (nleft > 0) {
		if ( (nread = recvfrom(fd, ptr, nleft, flags, souraddr, sourlen)) < 0) {
			if (errno == EINTR)
				nread = 0;		/* and call read() again */
			else
				return(-1);
		} else if (nread == 0)
			break;				/* EOF */

		nleft -= nread;
		ptr   += nread;
	}
	return(n - nleft);		/* return >= 0 */
}
/* end readn */

ssize_t						/* Write "n" bytes to a descriptor. */
sendton(int fd, const void *vptr, size_t n, int flags,
        const struct sockaddr *destaddr, socklen_t destlen)
{
	size_t		nleft;
	ssize_t		nwritten;
	const char	*ptr;

	ptr = vptr;
	nleft = n;
	while (nleft > 0) {
		if ( (nwritten = sendto(fd, ptr, nleft, flags, destaddr, destlen)) <= 0) {
			if (nwritten < 0 && errno == EINTR)
				nwritten = 0;		/* and call write() again */
			else
				return(-1);			/* error */
		}

		nleft -= nwritten;
		ptr   += nwritten;
	}
	return(n);
}
/* end writen */
















