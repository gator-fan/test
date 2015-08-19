/*************************************************************************
 * @File Name: forkmmap.c
 * @Author: wangfan
 * @Mail: wangfan@mvad.com 
 * @Created Time: 2015年08月13日 星期四 18时08分48秒
 ************************************************************************/

#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct {
  char name[4];
  int age;
} people;

int main(int argc, char** argv)
{
  int i;
  people *p_map;
  char temp;
  p_map = (people*) mmap(NULL, sizeof(people)*10, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
  if(fork() == 0)
  {
    sleep(2); 
    for(i = 0; i < 5; i++)
      printf("child read: the %d people's age is %d\n", i+1, (*(p_map+i)).age);
    munmap(p_map, sizeof(people)*10);
    exit(1);
  }
  temp = 'a';
  for(i = 0; i < 5; i++)
  {
    temp += 1;
    memcpy((*(p_map+i)).name, &temp, 1);
    (*(p_map+i)).age = 20+i;
  }
  sleep(5);
  printf("parent read: the 1st people's age is %d\n", (*p_map).age);
  printf("parent read: the 2nd people's age is %d\n", (*(p_map+1)).age);
  printf("unmap started\n");
  munmap(p_map, sizeof(people)*10);
  printf("unmap finished\n");

}
