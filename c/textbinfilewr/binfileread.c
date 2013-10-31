#include<stdio.h>

int main(int argc,char* argv[])
{
	FILE* pfile;
	unsigned int  data;
	if(argc<2)
	{
		fprintf(stderr,"input a binfile name for reading\n");
	}
	pfile=fopen(argv[1],"rb");
	printf("Read datas in binfile .\n");
	fread(&data,sizeof(unsigned int),1,pfile);
	for(;!feof(pfile);) {
		printf("%d ",data);
		fread(&data,sizeof(unsigned int),1,pfile);
	}
	putchar('\n');
	fclose(pfile);
	return 0;
}
