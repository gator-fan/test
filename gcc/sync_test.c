/*************************************************************************
 * @File Name: sync_test.c
 * @Author: wangfan
 * @Mail: wangfan@mvad.com 
 * @Created Time: 2015年07月27日 星期一 10时44分19秒
 ************************************************************************/

#include <stdio.h>

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define TEST_ROUND  20000
#define THREAD_NUM  10

static volatile int count = 0;
static volatile int count2 = 0;

void *test_func(void *arg)
{
  int i = 0;
  for(i = 0; i < TEST_ROUND; i++){
    __sync_fetch_and_add(&count, 1);
  }
  return NULL;
}

void *test_func(void *arg)
{
  int i = 0;
  for(i = 0; i < TEST_ROUND; i++){
    __sync_fetch_and_add(&count2, 1);
  }
  return NULL;
}

int main(int argc, const char *argv[])
{
  pthread_t thread_ids[THREAD_NUM];
  int i = 0;

  for(i = 0; i < sizeof(thread_ids)/sizeof(pthread_t); i++){
    pthread_create(&thread_ids[i], NULL, test_func, NULL);
  }

  for(i = 0; i < sizeof(thread_ids)/sizeof(pthread_t); i++){
    pthread_create(&thread_ids[i], NULL, test_func2, NULL);
  }

  for(i = 0; i < sizeof(thread_ids)/sizeof(pthread_t); i++){
    pthread_join(thread_ids[i], NULL);
  }

  printf("count=%d\r\n", count);
  return 0;
}
