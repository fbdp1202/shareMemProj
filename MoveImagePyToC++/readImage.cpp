#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <opencv2/highgui.hpp>

int main(int argc, const char **argv)
{
   int shmid, shmid_s;
   // give your shared memory an id, anything will do

   key_t key = 123459;
   key_t key_s = 123460;

   char *buffer;
   char *str_s;
   void *share_str = (void *)0;
   void *share_str_s = (void *)0;

   shmid = shmget(key, sizeof(char)*50000, 0666|IPC_CREAT);
   shmid_s = shmget(key_s, sizeof(char)*11, 0666|IPC_CREAT);

   if (shmid == -1 || shmid_s == -1) {
      perror("shmget failed : ");
      exit(0);
   }

   share_str = shmat(shmid, (void *)0, 0666|IPC_CREAT);
   share_str_s = shmat(shmid_s, (void *)0, 0666|IPC_CREAT);
   if (share_str == (void *)-1 || share_str_s == (void *)-1)
   {
      perror("shmat attach is failed : ");
      exit(0);
   }
   buffer = (char *)share_str;
   str_s = (char *)share_str_s;
   int count = 1;
   while (count < 3000) {
      printf("length: %s", str_s);
      int i =0, length=0;
      while (str_s[i] != '\n' && str_s[i] != '\0') {
         length *=10;
         length += (str_s[i]-'0');
         i++;
      }
      printf("length: %d\n", length);

      cv::Mat matImg;
      matImg = cv::imdecode(cv::Mat(1, length, CV_8UC1, buffer), CV_LOAD_IMAGE_UNCHANGED);

      char fileName[30];
      sprintf(fileName, "out/output_%04d.jpg", count);
      cv::imwrite(fileName, matImg);
      printf("Save file: %s\n", fileName);
      count++;
   }
   // Detach and remove shared memory
   // shmdt(&shmid);
   // shmctl(shmid, IPC_RMID, NULL);
   return 0;
}