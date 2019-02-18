#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

int main(int argc, const char **argv)
{
   int shmid;
   // give your shared memory an id, anything will do
   key_t key = 123456;
   char *shared_memory;
   char str[] = "memory";
   printf("print the string : ");
   scanf("%s", str);

   // Setup shared memory, 11 is the size
   if ((shmid = shmget(key, 11, IPC_CREAT | 0666)) < 0)
   {
      printf("Error getting shared memory id");
      exit(1);
   }

   // Attached shared memory
   // if ((shared_memory = shmat(shmid, (void *)0, 0)) == (void *) -1)
   // {
   //    printf("Error attaching shared memory id");
   //    exit(1);
   // }
   // int* restrict num=&a;

   // copy "hello world" to shared memory
   memcpy(shared_memory, str, sizeof(str));

   // sleep so there is enough time to run the reader!
   sleep(1000);

   // Detach and remove shared memory
   shmdt(&shmid);
   shmctl(shmid, IPC_RMID, NULL);

}