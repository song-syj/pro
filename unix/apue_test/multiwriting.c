#include <sys/sem.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#define MAXDATALEN 1000
typedef struct data_fragment {
	unsigned char data[MAXDATALEN];
	unsigned short size;
	int offset;
}data_fragment;

	int semid;

union semun {
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

void myhandler(int signo, siginfo_t *si, void *vcontext);

int main(int argc, char *argv[])
{
	pid_t pid;
	int read_fd, write_fd;
	int pipe_fd[2];
	int file_size;
	int file_offset;
	int status;
	int number;// the size of subprocesses;
	int i;
	data_fragment tempdata;
	union semun sem_init;
	struct sigaction act, oldact;
	struct sembuf readsem, writesem;
	int key_sem;
	int readsize;

	if (argc < 4) {
		fputs("the number or arg is less than 3!\n", stderr);
		exit(1);
	}
	
	if ((read_fd = open(argv[1], O_RDONLY)) < 0) {
		fprintf(stderr, "open reading file : %s\n", strerror(errno));
		exit(1);
	}
	
	if ((write_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0600)) < 0) {
		fprintf(stderr, "open writing file : %s\n", strerror(errno));
		exit(1);
	}

	number = atoi(argv[3]);
	if(pipe(pipe_fd) < 0) {
		perror("create a pipe error");
		exit(1);
	}
	
	tempdata.size = 0;
	tempdata.offset = 0;
	file_size = lseek(read_fd, 0, SEEK_END);
	lseek(read_fd, 0,SEEK_SET);
	file_offset = 0;
	key_sem = ftok("/etc/", 0x45);
	if (key_sem < 0) {
		perror("ftok sem error");
		exit(1);
	}

	semid = semget(key_sem, 3, IPC_CREAT | IPC_EXCL | 0600);
	if (semid < 0) {
		perror("creat a sem error");
		exit(1);
	}
	sem_init.val = 0;
	semctl(semid, 0, SETVAL, sem_init);
	sem_init.val = 4;
	semctl(semid, 1, SETVAL, sem_init);
	
	act.sa_sigaction = myhandler;
	act.sa_flags = SA_SIGINFO|SA_RESETHAND;
	sigaction(SIGINT, &act,&oldact);

	
	for (i = 0; i < number; i ++) {
		if ((pid = fork()) < 0) {
			perror("fork a process error");
			exit(1);
		} else if (pid == 0) {
			close(pipe_fd[1]);
			
			readsem.sem_num = 0;
			readsem.sem_op = -1;
			readsem.sem_flg = 0;
			writesem.sem_num = 1;
			writesem.sem_op = 1;
			writesem.sem_flg = 0;
			
			do {
				semop(semid, &readsem,1);
				readsize = read(pipe_fd[0], &tempdata, sizeof(data_fragment));
				semop(semid, &writesem,1);
				if (readsize == sizeof(data_fragment)) {
					pwrite(write_fd, tempdata.data, tempdata.size, tempdata.offset);
				}else if (readsize == 0){
					//					fputs("pipe empty\n", stdout);
					break;
				}else if ( readsize < sizeof(data_fragment)) {
					fprintf(stdout, "read part of data fragment\n");
				}
				else {
					perror("read pipe");
					exit(1);
				}

			} while (readsize == sizeof (data_fragment) 
					 && (tempdata.size+tempdata.offset) < file_size);
			return 3;
		}
	}
	
	close (pipe_fd[0]);
	readsem.sem_num = 0;
	readsem.sem_op =  1;
	readsem.sem_flg = 0;
	writesem.sem_num = 1;
	writesem.sem_op = -1;
	writesem.sem_flg = 0;

	fputs("start copying!\n", stdout);
	do {
		semop(semid, &writesem, 1);
		readsize =  read(read_fd, tempdata.data, MAXDATALEN);
		semop(semid, &readsem, 1);
		if (readsize < 0) {
			perror("main process read file");
			semctl(semid, 0,IPC_RMID);
			exit(1);
		}else if (readsize == 0) {
			break;
		}
		tempdata.offset = file_offset;
		file_offset += readsize;
		tempdata.size = readsize;
		write(pipe_fd[1], &tempdata, sizeof(data_fragment));
	} while (readsize == MAXDATALEN);

	close(pipe_fd[1]);
	wait(&status);
	fputs("copying finished!\n", stdout);
	semctl(semid, 0, IPC_RMID);

	return 0;
}

void
myhandler(int signo, siginfo_t *si, void *vcontext)
{
    puts("delete operation");
    semctl(semid, 0, IPC_RMID);
	exit(1);
}
