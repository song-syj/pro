#include"apue.h"

int 
main(void)
{
	char *ptr;
	int size;
	ptr=path_alloc(&size);
	if(getcwd(ptr,size)==NULL)
		err_sys("getcwd failed");
	printf("cwd = %s\n",ptr);
	if(chdir("/home/song")<0)
		err_sys("chdir failed");
	if(getcwd(ptr,size)==NULL)
		err_sys("getcwd failed");
	printf("cwd = %s\n",ptr);
	exit(0);
}
