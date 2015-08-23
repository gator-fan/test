#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *print_thread(void *arg){
	while(true)
		printf("current thread id is %u\n", (unsigned) pthread_self());
}

int main(int argc, char *argv[])
{
	pthread_t thread;
	pthread_create(&thread, NULL, print_thread, NULL);
	sleep(1);
	printf("main thread id is %u\n", (unsigned)pthread_self());
	return 0;
}
