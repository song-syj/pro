/* My solution to homework problems of chapter 8 in caspp
 * Date: 2014.04.09
 * Reference: Stackverflow website and others
 */

/* 8.20 */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[], char *env[])
{
	 char *col;

	 col = getenv("COLUMNS");
	 if(col == NULL) {
		  printf("output is %d columns\n", 80);
	 } else {
		  printf("output is %s columns\n", col);
	 }
	 
	 execve("/bin/ls", argv, env);

	 exit(0);
}


/* 8.22 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>

extern char **environ;

int mysystem(char *command)
{
	 pid_t pid;
	 int status;
	 char *argv[4];
	 
	 if (command == NULL)
		  return -1;

	 if((pid = fork()) < 0)
		  return -1;

	 if(pid == 0) {
		  argv[0] = "/bin/sh";
		  argv[1] = "-c";
		  argv[2] = command;
		  argv[3] = NULL;

		  execve(argv[0], argv, environ);

		  return -1;
	 }

	 while (1) {
		  pid = waitpid(-1, &status, 0);
		  if(pid == -1) {
			   if(errno != EINTR)
					return -1;
		  } else {
			   if(WIFEXITED(status))
					return (WEXITSTATUS(status));
			   else
					return status;
		  }
	 }
}


int
main(int argc, char *argv[])
{
	 int  status;
	 
	 if(argc < 2) {
		  printf("usage: ./a.out <arg>!\n");
		  exit(0);
	 }
	 
	 status = mysystem(argv[1]);
	 
	 printf("%s : %d\n", argv[1], status);
	 
	 return 0;
}

/* 8.24 */
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define N 2

int main() 
{
    int status, i;
	char msg[100];
    pid_t pid;

    /* Parent creates N children */
    for (i = 0; i < N; i++)                       //line:ecf:waitpid1:for
		 if ((pid = fork()) == 0)  /* child */     //line:ecf:waitpid1:fork
			  (*(void (*)())(0))();

    /* Parent reaps N children in no particular order */
    while ((pid = waitpid(-1, &status, 0)) > 0) { //line:ecf:waitpid1:waitpid
		 if (WIFEXITED(status))                    //line:ecf:waitpid1:wifexited
			  printf("child %d terminated normally with exit status=%d\n",
					 pid, WEXITSTATUS(status));     //line:ecf:waitpid1:wexitstatus
		 else if (WIFSIGNALED(status)) {
			  snprintf(msg, 100,
					  "child %d terminated by signal %d ",
					  pid, WTERMSIG(status));
			  psignal(WTERMSIG(status), msg);
		 } else
			  printf("child %d terminated abnormally\n", pid);
    }

    /* The only normal termination is if there are no more children */
    if (errno != ECHILD)                          //line:ecf:waitpid1:errno
		 printf("waitpid error");

    exit(0);
}

/* 8.25 */

#include <unistd.h>
#include <setjmp.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void *Signal(int signum, void *handler)
{
	 struct sigaction action, old_action;

	 action.sa_handler = handler;
	 sigemptyset(&action.sa_mask);
	 action.sa_flags = SA_RESTART;

	 if(sigaction(signum, &action, &old_action) < 0) {
		  printf("Signal error: %s\n", strerror(errno));
		  exit(0);
	 }

	 return old_action.sa_handler;
}

sigjmp_buf buf;

void handler(int signum)
{
	 siglongjmp(buf, 1);
}


char *tfgets(char *s, int size, FILE *stream)
{
	 Signal(SIGALRM, handler);
	 
	 if (alarm(5) < 0) {
		  printf("Alarm error: %s\n", strerror(errno));
		  exit(0);
	 }

	 if(sigsetjmp(buf, 1) == 0) {
		  return fgets(s, size, stream);
	 } else {
		  return NULL;
	 }
}

int main()
{
	 char buffer[100];
	 
	 while(1) {
		  
		  if(tfgets(buffer, 100, stdin) != NULL)
			   printf("read : %s", buffer);
		  else
			   printf("time out \n");
		  
	 }

	 return 0;
}


