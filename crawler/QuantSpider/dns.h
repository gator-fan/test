#ifndef _DNS_H
#define _DNS_H

#include<event2/dns.h>
#include<event2/util.h>
#include<event2/event.h>
#include<map>
#include<string>
#include"url.h"

using namespace std;

extern map < string, string > host_ip_map;
extern pthread_mutex_t map_lock;

typedef struct {
	Url *uu;
	int *pp;
	struct event_base *bb;
} dns_cb_arg;

void dns_callback(int errcode, struct evutil_addrinfo *addr, void *ptr)
{
	dns_cb_arg *arg = (dns_cb_arg *) ptr;
	Url *myurl = arg->uu;
	//printf("DNS callback:%s\n",myurl->domain);
	if (errcode) {
		//printf("DNS resolution error：%s -> %s\n", myurl->host, evutil_gai_strerror(errcode));
	} else {
		struct evutil_addrinfo *ai;
		for (ai = addr; ai->ai_next; ai = ai->ai_next) {
		}		/*get last IP */
		char buf[128];
		const char *s = NULL;
		if (addr->ai_family == AF_INET) {
			struct sockaddr_in *sin =
			    (struct sockaddr_in *)ai->ai_addr;
			s = evutil_inet_ntop(AF_INET, &sin->sin_addr, buf, 128);	// change from struct into xxx.xxx.xxx.xxx
		} else if (addr->ai_family == AF_INET6) {
			struct sockaddr_in6 *sin6 =
			    (struct sockaddr_in6 *)ai->ai_addr;
			s = evutil_inet_ntop(AF_INET6, &sin6->sin6_addr, buf,
					     128);
		}
		if (s) {
			//printf("set %s with IP:%s\n",myurl->domain,s);
			strcpy(myurl->ip, s);
			char *host = strdup(myurl->domain);
			char *ip = strdup(myurl->ip);
			pthread_mutex_lock(&map_lock);
			host_ip_map[host] = ip;
			pthread_mutex_unlock(&map_lock);
		}
		evutil_freeaddrinfo(addr);
	}
	//printf("DNS callback succeed |%s||%s|\n",myurl->domain,myurl->ip);
	//freeURL(myurl);
	if (--(*(arg->pp)) == 0) {
		//printf("event_base loop will exit\n");
		event_base_loopexit(arg->bb, NULL);	/*no timeout, exit loop*/
	}
}

void dnsParse(Url ** ptr, int count)
{
	struct event_base *base;
	struct evdns_base *dnsbase;
	//sleep(3);             //dns resolution is much faster than download, so sleep
	//printf("start to DNS resolution\n");
	int n_pending_requests = 0;
	base = event_base_new();	/*initialize event base */
	if (!base) {
		perror("event_base_new");
		return;
	}
	dnsbase = evdns_base_new(base, 1);	/*1 default dns configuration，0 no configuration*/
	if (!dnsbase) {
		perror("evdns_base_new");
		return;
	}

	int i;
	for (i = 0; i < count; ++i) {
		struct evutil_addrinfo hints;
		struct evdns_getaddrinfo_request *req;
		memset(&hints, 0, sizeof(hints));

		hints.ai_family = AF_UNSPEC;	/*both AF_INET and AF_INET6 are fine*/
		/*if not set socktype，got two address，one for TCP，the other for UDP*/
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		++n_pending_requests;
		dns_cb_arg *arg = (dns_cb_arg *) calloc(sizeof(dns_cb_arg), 1);
		arg->uu = ptr[i];
		arg->pp = &n_pending_requests;
		arg->bb = base;
		//printf("begin to send DNS request:%s\n",arg->uu->domain);
		req = evdns_getaddrinfo(dnsbase, arg->uu->domain, NULL, &hints,
				      dns_callback, arg);
		if (req == NULL) {
			fprintf(stderr, "DNS request：%s return imeediately\n", ptr[i]->domain);
		}
	}
	if (n_pending_requests)
		event_base_dispatch(base);

	evdns_base_free(dnsbase, 0);
	event_base_free(base);
	//printf("release event_base和dns_base\n");
}

#endif
