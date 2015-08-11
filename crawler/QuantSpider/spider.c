#include<pthread.h>
#include"bloom.h"
#include"url.h"
#include"dns.h"
#include"http.h"

#define MAX_QUEUE_SIZE 300

map <string, string> host_ip_map;
queue <Url *>url_queue;
// ev is used to register events, events[10] is used to event callback
struct epoll_event ev, events[10];
int epfd;
pthread_mutex_t map_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t queue_lock = PTHREAD_MUTEX_INITIALIZER;

void putlinks2queue(char *links[], int count);
void addurl2queue(Url * url);
int CreateThread(void *(*start_routine) (void *), void *arg, pthread_t * thread,
		 pthread_attr_t * pAttr);

int main(int argc, char *argv[])
{
	int i, n;
	if (argc < 2) {
		printf("Usage:%s www.sogou.com/ www.cnblogs.com/cate/c\n", argv[0]);
		return 0;
	}
	chdir("downpage");
	putlinks2queue(argv + 1, argc - 1);	// put init urls

	epfd = epoll_create(50);
	n = url_queue.size() < 50 ? url_queue.size() : 50;	/*50 socket connection at most for concurrency*/
	for (i = 0; i < n; ++i) {
		pthread_mutex_lock(&queue_lock);
		Url *url = url_queue.front();
		url_queue.pop();
		pthread_mutex_unlock(&queue_lock);
		//printf("fetch from url queue：%s%s-->%s\n",url.domain,url.path,url.ip);
		int sockfd;
		//printf("before sending connect...\n");
		int rect = buildConnect(&sockfd, url->ip);
		setnoblocking(sockfd);	/* set sockfd non-blocking*/
		//printf("before sending http request...\n");
		rect = sendRequest(url, sockfd);
		Ev_arg *arg = (Ev_arg *) calloc(sizeof(Ev_arg), 1);
		arg->url = url;
		arg->fd = sockfd;
		ev.data.ptr = arg;
		ev.events = EPOLLIN | EPOLLET;
		printf("add %d[%s%s] into epoll\n", sockfd, url->domain,
		       url->path);
		epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &ev);	//register event into ev
	}

	while (1) {
		n = epoll_wait(epfd, events, 10, 2000);	/*wait for sockfd readable，namely waiting for http response */
		printf("[%d] sockfd is ready to read\n", n);
		for (i = 0; i < n; ++i) {
			Ev_arg *arg = (Ev_arg *) (events[i].data.ptr);
			//printf("%d is ready to read\n",arg->fd);
			CreateThread(recvResponse, arg, NULL, NULL);
		}
	}
	close(epfd);
}

/**
 * @Param: count, number of urls
 *
 */
void putlinks2queue(char *links[], int count)
{
	int i = 0, num = 0;
	Url **urls;
	urls = (Url **) calloc(count, sizeof(Url *));
	for (i = 0; i < count; ++i) {
		if (links[i] == NULL)
			continue;
		char *h = (char *)calloc(MAX_LINK_LEN, 1);
		char *r = (char *)calloc(MAX_LINK_LEN, 1);
		char *iipp = (char *)calloc(20, 1);
		pretreatLink(links[i]);
		if (links[i] == NULL)
			continue;
		getHRfromlink(links[i], h, r);
		//printf("h=%s\tr=%s\n",h,r);
		if (bloomDomain(h)) {	/*domain exist*/
			if (bloomPath(r)) {	/*path exist，ingore this link */
				free(h);
				free(r);
				free(iipp);
				continue;
			} else {	/*path not exist*/
				Url *tmp = (Url *) calloc(1, sizeof(Url));
				tmp->domain = h;
				tmp->path = r;

				map<string, string>::const_iterator itr;
				itr = host_ip_map.find(h);	/*lookup domain*/
				if (itr == host_ip_map.end()) {	/*domain not in map*/
					tmp->ip = iipp;
					urls[num++] = tmp;	/*add it to urls，wait for batch DNS resolution */
					//printf("|%s||%s||%s| is added to DNS resolution queue\n",urls[num-1]->domain,urls[num-1]->ip,urls[num-1]->path);
				} else {	/*domain in map */
					tmp->ip = strdup(host_ip_map[h].c_str());	/*get ip from map for domain */
					//printf("get ip from map：%s\t%s\t%s\n",tmp->domain,tmp->ip,tmp->path);
					addurl2queue(tmp);	/*put url into url queue */
					continue;
				}
			}
		} else {	/*domain not exist */
			Url *tmp = (Url *) calloc(1, sizeof(Url));
			tmp->domain = h;
			tmp->path = r;
			tmp->ip = iipp;
			urls[num++] = tmp;	/*added into urls，wait for DNS resolution */
			//printf("|%s||%s||%s| is added into DNS resolution queue\n",urls[num-1]->domain,urls[num-1]->ip,urls[num-1]->path);
		}
	}

	dnsParse(urls, num);	/*batch DNS resolution*/

	for (i = 0; i < num; ++i)	/*after DNS resolution and get ip，put them into url queue */
		addurl2queue(urls[i]);
	//printf("put links into url_queue done\n");    
	//free(urls);
}

/*put url into url_queue*/
void addurl2queue(Url * url)
{
	if (url == NULL || url->domain == NULL || strlen(url->domain) == 0
	    || url->path == NULL || strlen(url->path) == 0 || url->ip == NULL
	    || strlen(url->ip) == 0) {
		fprintf(stderr,
			"Url is not complete: domain=%s\tpath=%s\tip=%s\n",
			url->domain, url->path, url->ip);
		exit(1);
	}
	//fprintf(stderr,"Url is complete:domain=%s\tpath=%s\tip=%s\n",url->domain,url->path,url->ip);
	if (url_queue.size() >= MAX_QUEUE_SIZE)	/*if queue is full，just ignore this url */
		return;
	pthread_mutex_lock(&queue_lock);
	url_queue.push(url); // url_queue is the queue crawler needed to crawler
	pthread_mutex_unlock(&queue_lock);
	//printf("%s%s is added into url_queue\n",url->domain,url->path);
}

/*create detached threads*/
int CreateThread(void *(*start_routine) (void *), void *arg, pthread_t * thread,
		 pthread_attr_t * pAttr)
{
	pthread_attr_t thr_attr;
	if (pAttr == NULL) {
		pAttr = &thr_attr;
		pthread_attr_init(pAttr);	/*initialize thread attributes*/
		pthread_attr_setstacksize(pAttr, 1024 * 1024);	/*set the default size of stack as 1M */
		pthread_attr_setdetachstate(pAttr, PTHREAD_CREATE_DETACHED);	/*detached child thread，parent don't need to wait for child*/
	}
	pthread_t tid;
	if (thread == NULL) {
		thread = &tid;
	}
	int r = pthread_create(thread, pAttr, start_routine, arg);
	pthread_attr_destroy(pAttr);	/*destroy thread attribute*/
	return r;
}
