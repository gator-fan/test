#ifndef _HTTP_H
#define _HTTP_H

#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/epoll.h>
#include<queue>
#include<sys/stat.h>
#include<fcntl.h>

#include"url.h"

int connect_pending = 0;
pthread_mutex_t connlock = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
	Url *url;
	int fd;
} Ev_arg;

extern queue < Url * >url_queue;
extern int epfd;
extern struct epoll_event ev;
extern struct epoll_event events[10];
extern pthread_mutex_t queue_lock;

void setnoblocking(int sockfd)
{
	int opts;
	opts = fcntl(sockfd, F_GETFL);
	if (opts < 0) {
		perror("fcntl(sockfd,GETFL)");
		exit(1);
	}
	opts |= O_NONBLOCK;	
	if (fcntl(sockfd, F_SETFL, opts) < 0) {
		perror("fcntl(sockfd,SETFL)");
		exit(1);
	}
}

int buildConnect(int *client_sockfd, char *ip)
{
	struct sockaddr_in server_address;
	bzero(&server_address, sizeof(struct sockaddr_in));
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(80);
	if (inet_aton(ip, &(server_address.sin_addr)) != 1) {	// anaylise ip address into struct
		perror("inet_pton");
		printf("ip=%s\n", ip);
		return -1;
	}
	if ((*client_sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		return -1;
	}
	if (connect(*client_sockfd, (struct sockaddr *)&server_address,
	     sizeof(struct sockaddr_in)) == -1) {
		close(*client_sockfd);
		perror("connect");
		return -1;
	}
	pthread_mutex_lock(&connlock);
	connect_pending++;
	pthread_mutex_unlock(&connlock);
	return 0;
}

int sendRequest(Url * url, int fd)
{
	char request[1024] = { 0 };
	sprintf(request, "GET %s HTTP/1.0\r\nHost: %s\r\n\r\n", url->path,
		url->domain);
	int need = strlen(request);	/*num needs to be write into sockfd*/
	int tmp = 0;		/*num of data sent*/
	int n;			// record real num of data processed
	while (need > 0) {
		n = write(fd, request + tmp, need);
		if (n < 0) {
			if (errno == EAGAIN) {	/*queue full， retry later*/
				usleep(1000);
				continue;
			}
			freeUrl(url);	/*other error, return -1, send fail, and release url */
			close(fd);
			return -1;
		}
		need -= n;
		tmp += n;
	}
	//fprintf(stderr,"Send http request succeed ==>%s%s\n",url->host,url->resource);
	return 0;
}

/*fetch html response，write inot file and fetch hyper-link and put it into url-queue*/
void *recvResponse(void *argument)
{
	Ev_arg *arg = (Ev_arg *) argument;
	Url *url = arg->url;
	int fd = arg->fd;
  // use url as file name, change slash into underline
	char *fn = link2fn(url);
	int htmlfd = open(fn, O_WRONLY | O_CREAT | O_APPEND, 0644);

	if (htmlfd < 0) {
		fprintf(stderr,
			"In recvResponse(), failed to open %s \n%s\t%s\n",
			fn, url->domain, url->path);
		//freeUrl(url);
		close(fd);
		return NULL;
	}
	free(fn);

	//printf("start to download %d[%s%s]\n",fd,url->domain,url->path);
	int i, n, need, ll = 0;
	char buf[1024] = { 0 };
	while (1) {
		need = sizeof(buf) - 1 - ll;
		n = read(fd, buf, need);
		if (n < 0) {
			if (errno == EAGAIN) {
				usleep(1000);
				continue;
			} else {
				fprintf(stderr, "Read http response error\n");
				//freeUrl(url);
				close(htmlfd);
				return NULL;
			}
		} else if (n == 0) {	/*Read http response finished*/
			break;
		} else {	/*read again*/
			//printf("read from socket:|%s|\n",buf);
			write(htmlfd, buf, n);
			ll = extractLink(buf, url->domain);
		}
	}
	close(htmlfd);
	//fprintf(stderr,"get http response succeed==>%s%s\n",url->host,url->resource);
	//freeUrl(url);
	pthread_mutex_lock(&connlock);
	connect_pending--;
	pthread_mutex_unlock(&connlock);

	if (connect_pending < 50)
		n = 2;
	else
		n = 1;
	printf("Thread is going to start %d socket connections\n", n);
	for (i = 0; i < n; ++i) {
		if (url_queue.empty())	/*url_queue empty, rest 0.5 s */
			usleep(500000);
		pthread_mutex_lock(&queue_lock);
		Url *url = url_queue.front();
		url_queue.pop();
		pthread_mutex_unlock(&queue_lock);
		int sockfd;
		int rect = buildConnect(&sockfd, url->ip);
		setnoblocking(sockfd);
		rect = sendRequest(url, sockfd);
		Ev_arg *arg = (Ev_arg *) calloc(sizeof(Ev_arg), 1);
		arg->url = url;
		arg->fd = sockfd;
		ev.data.ptr = arg;
		ev.events = EPOLLIN | EPOLLET;
		printf("Put %d[%s%s] into epoll\n", sockfd, url->domain,
		       url->path);
		epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &ev);	//register to ev
	}
	return NULL;
}

#endif
