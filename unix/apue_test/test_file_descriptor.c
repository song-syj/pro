#include"apue.h"
#include<fcntl.h>
#include<stdio.h>
#include<string.h>

int main(void)
{
	int fd;
	char buff[]="close stdout and print the string to the file_descrpitor";
	close(1);
	fd=open("flie_descriptor",O_RDWR|O_CREAT|O_TRUNC,644);
	//printf("the descriptor of the opened file is %d\n",fd);
	write(STDOUT_FILENO,buff,strlen(buff));
}
