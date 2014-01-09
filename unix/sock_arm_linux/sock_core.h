#ifndef SOCK_CORE_H
#define SOCK_CORE_H

#include <sys/socket.h>
#define MAXLINE 1024
#define LISTENQ 100
#define SERV_PORT 8088
#define SERV_DATA_PORT 8090
#define RECVBUFFSIZE (64*1024)
#define SENDBUFFSIZE (64*1024)
typedef const struct sockaddr SA;

int create_sock(int family, int type, int protol);
void bind_sock(int fd, const struct sockaddr *sa, socklen_t len);
void listen_sock(int sockfd, int backlog );
int accept_sock(int sockfd, const struct sockaddr *cliaddr, socklen_t *len);
void connect_sock(int sockfd,const struct sockaddr *servaddr, socklen_t len);

ssize_t readline(int fd, void *vptr, size_t maxlen);
ssize_t readstring(int fd, void *vptr, size_t maxlen);
ssize_t readn(int fd, void *vptr, size_t n);
ssize_t writen(int fd, const void *vptr, size_t n);

ssize_t recvfromn(int sockfd, void *buff, size_t nbytes, int flags,
                  struct sockaddr *from, socklen_t *addrlen);
 
ssize_t sendton(int sockfd, const void *buff, size_t nbytes, int flags,
                const struct sockaddr *to, socklen_t addrlen);
 

    
#endif








