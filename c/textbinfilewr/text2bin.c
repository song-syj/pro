#include<stdio.h>

int main(int argc,char* argv[])
{
	FILE* pfText;
	FILE* pfBin;
	unsigned int data;
	int i=0;
	pfText=fopen(argv[1],"r");
	pfBin=fopen(argv[2],"wb");

	fscanf(pfText,"%x",&data);
	while(!feof(pfText))
	{
		i++;
		fwrite(&data,sizeof(unsigned int),1,pfBin);
		fscanf(pfText,"%x",&data);
	}
	printf("%d\n",i);
	printf("Read a %d integer in text file!\n",i);
	printf("The last data is %d !\n",data);
	printf("Text file to bin file.\n");
	fclose(pfText);
	fclose(pfBin);
	return 0;
}
