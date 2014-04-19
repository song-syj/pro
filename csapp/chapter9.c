/* problem 9.5 */
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void mmapcopy(int fd, int size)
{
	 char *buf;
	 int err;

	 buf = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
	 if(buf == MAP_FAILED) {
		  fprintf(stderr, "mmap error: %s\n", strerror(errno));
		  exit(1);
	 }

	 write(1, buf, size);

	 err = munmap(buf, size);
	 if (err == -1) {
		  fprintf(stderr, "munmap error: %s\n", strerror(errno));
		  exit(1);
	 }
}

int main(int argc, char *argv[])
{
	 int fd;
	 struct stat stat;
	 
	 if (argc < 2) {
		  printf("usage: %s <filename>\n", argv[0]);
		  exit(0);
	 }

	 fd = open(argv[1], O_RDONLY, 0);

	 fstat(fd, &stat);
	 mmapcopy(fd, stat.st_size);
	 
	 return 0;
}
