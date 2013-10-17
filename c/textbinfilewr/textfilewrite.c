#include<stdio.h>

int main(int argc,char* argv[])
{
	FILE* pfile;
	unsigned int i;
	if(argc<2)
	{
		fprintf(stderr,"input a textfile name for writing!\n");

		return 1;
	}
	pfile=fopen(argv[1],"w");
	for(i=0;i<100;i++)
		fprintf(pfile,"%x\n",i);
	fclose(pfile);
	printf("Write 0-99 in text file!\n");
	return 0;
}
