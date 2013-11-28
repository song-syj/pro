#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
//#include <sys/stat.h>
//#include <sys/types.h>
#include <termio.h>
#include "uart.h"

/*
  function : open a device
  input : dev: a name the device used
  output : a file descriptor that poionts the device
 */
int
open_uart(char *dev) {
	int fd;
	if((fd = open(dev, O_RDWR | O_NOCTTY)) < 0) {//
		fputs("open %s error\n",stderr);
		exit(1);
	}

	return fd;
		
}
/*
  function : set the argument of the serial port
  input : fd a file descriptor for a device taht you opened
         speed the serial communication speed
		 data_bits the width of the sent data one time, the value can be 7, 8
		 stop_bist a character in asynchronous communication that lets a receiver know that the byte being transmitted has ended. Its value can be 1,2.
		 partity a charater that check the sent data
  
 */
void
set_uart_configure(int fd, int speed,int data_bits,
				  int stop_bits, char parity)
{
	int status;
	struct termios opt;
	bzero(&opt, sizeof(opt));
	
	//set receiving enable
	opt.c_cflag |= (CLOCAL | CREAD);
	//set data bits
	opt.c_cflag &= ~CSIZE;
	switch (data_bits) {
	case 7:
		opt.c_cflag |= CS7;
		break;
	case 8:
		opt.c_cflag |= CS8;
		break;
	default:
		opt.c_cflag |= CS8;
		break;
	}

	//set stop bits
	switch (stop_bits) {
	case 1:
		opt.c_cflag &= ~CSTOPB;
		break;
	case 2:
		opt.c_cflag |= CSTOPB;
		break;
	default :
		fputs("set stop_bits error\n",stderr);
	}

	//set parity check
	switch (parity) {
	case 'n':
	case 'N':
		opt.c_cflag &= ~PARENB;
		opt.c_iflag &= ~INPCK;
		break;
	case 'o':
	case 'O':
		opt.c_cflag |= PARENB;
		opt.c_cflag |= PARODD;
		opt.c_iflag |= INPCK;
		break;
	case 'e':
	case 'E':
		opt.c_cflag |= PARENB;
		opt.c_cflag &= ~PARODD;
		opt.c_iflag |= INPCK;
	case 's':
	case 'S':
		opt.c_cflag &= ~PARENB;
		opt.c_cflag &= ~CSTOPB;
		break;
	default:
		opt.c_cflag &= ~PARENB;
		opt.c_iflag &= ~INPCK;
	}
	
	//set serial baurd
	switch(speed) {
	case 2400:
		cfsetispeed(&opt,B2400);
		cfsetospeed(&opt,B2400);
		break;
	case 4800:
		cfsetispeed(&opt,B4800);
		cfsetospeed(&opt,B4800);
		break;
	case 9600:
		cfsetispeed(&opt,B9600);
		cfsetospeed(&opt,B9600);
		break;    
	case 57600:
		cfsetispeed(&opt,B57600);
		cfsetospeed(&opt,B57600);
		break;    
	case 115200:
		cfsetispeed(&opt,B115200);
		cfsetospeed(&opt,B115200);
		break;    
	default:
		cfsetispeed(&opt,B9600);
		cfsetospeed(&opt,B9600);
		break;    
	}
	opt.c_lflag |= (ICANON | ECHO);
	opt.c_iflag |= ICRNL;
	opt.c_oflag |= OPOST;
	opt.c_oflag |= ONLCR;
	//	opt.c_oflag |= OCRNL;
	/*opt.c_lflag &= ~(ICANON | ECHO);
	opt.c_cc[VTIME] = 0;
	opt.c_cc[VMIN] = 1;*/
	tcflush(fd, TCIFLUSH);
	if((tcsetattr(fd, TCSANOW, &opt)) < 0) {
		perror("tcsetattr");
		exit(1);
	}
	printf("set ttys success !\n");
}


