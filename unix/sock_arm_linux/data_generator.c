#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int fd;
    int i =0;
	char buff[100];
    if (argc < 2) {
        perror("usgage:<filename>");
        exit(1);
    }
    fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd < 0) {
        perror("open file");
        exit(1);
    }
    for (i = 0; i < 1000/*INT_MAX/128*/; i++) {
		sprintf(buff, "%04x\n", i);
        if (write(fd, buff, strlen(buff)) < 0) {
            perror("write file");
            exit(1);
        }
    }
    return 0;
}



