#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <string.h> 
#include <unistd.h> 
#define DATA_LENGTH 4096

int main()
{
	int shmid;
	int i;
	key_t key = 123457;

	char *str;
	void *share_str = (void *)0;
	// void *shared_memory = (void *)0;

// 공유메모리 공간을 만든다.
	shmid = shmget(key, sizeof(char)*DATA_LENGTH, 0666|IPC_CREAT);

	if (shmid == -1)
	{
		perror("shmget failed : ");
		exit(0);
	}

	share_str = shmat(shmid, (void *)0, 0666|IPC_CREAT);
	if (share_str == (void *)-1)
	{
		perror("shmat attach is failed : ");
		exit(0);
	}
	str = (char *)share_str;

	while(1)
	{
		fprintf(stderr,"[%s]\n",str);
		sleep(1);
	}
}