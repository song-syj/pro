#include<unistd.h>
#include<stdarg.h>
#include<stdio.h>

int myprintf(const char* fmt, ...);
int main(int argc,char* argv[])
{
	myprintf("Hello %Linux!");
	myprintf("my name is %s","syj");
	myprintf("the character is %c",'a');
	myprintf("the integer is %d",10);
	myprintf("the float is %f",12.8);
	return 0;
}

int myprintf(const char* fmt, ...)
{
	va_list ap;
	char buf[1000];
	char *str,*pstr;
	int i,len;
	float f;
	va_start(ap,fmt);
	for(str=buf;*fmt;fmt++)
	{
		if(*fmt!='%')
		{
			*str++=*fmt;
			continue;
		}
		fmt++;
		switch(*fmt){
			case'c':
				*str++=va_arg(ap,int);
				break;
			case's':
			 	pstr=va_arg(ap,char*);
				while(*pstr)
				{
					*str++=*pstr++;
				}
				break;
			/*case'd':break;
				*str++=va_arg(ap,int);
			case'f':break;
				f=va_arg(ap,float);
				while((int)f!=0&&i)
				str++=*/
			default:{
						*(str++)='%';
						if(*fmt)
						{
							*str++=*fmt;
						}
						else
							fmt--;
							break;
					}
		}
		
	}
	*str='\n';
	write(STDOUT_FILENO,buf,(str-buf+1));
	va_end(ap);
	return (str-buf);
}

void err_sys(const char* fmt,...)
{

}
