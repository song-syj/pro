#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <termios.h>
#include "uart.h"

int
main(int argc, char *argv[])
{
	int fd;
	struct termios oldio;
	char num;
	char dev[11] = "/dev/ttyS";
	char buff[100];
	int size;
	if (argc < 2) {
		fputs("arg number less than 2!\n",stderr);
 		exit(1);
	}
	// argv[1] indicate the number of ttyS
	num = argv[1][0];
	dev[9] = num;
	dev[10] = '\0';
	fd = open_uart(dev);

	//get the primitive set of ttys[num],num is the number of ttyS
	if (tcgetattr(fd, &oldio) < 0) {
		perror("tcgetattr oldio");
	}
	//set the serial ports 
	set_uart_configure(fd, 115200, 8, 1, 'N');
	//test ttyS
	memset(buff, 0, 100);
	//read data from ttyS[num] 
	size = read(fd, buff, 100);
	if (size < 0) { // read serial error
		perror("read serial");
		exit(1);
	} else {
		printf("received string:%s",buff);//print the string from serial port
		if(write(fd, buff, size) < 0) {
			perror("write serial");
			exit(1);
		}
		printf("test %s done\n",dev);
	}
	//recover the primitive set of the modified ttyS[num]
	tcsetattr(fd, TCSANOW, &oldio);
	
	return 0;
}
