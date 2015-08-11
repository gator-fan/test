#ifndef _URL_H
#define _URL_H

#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<regex.h>

#define MAX_LINK_LEN 128	/*FIXME, any hyper-link is longer than MAX_LINK_LEN will be ignored */

typedef struct {
	char *domain;
	char *ip;
	char *path;
} Url;

extern void putlinks2queue(char *links[], int count);

void freeUrl(Url * url)
{
	free(url->domain);
	free(url->ip);
	free(url->path);
	//free(url); //FIXME, not release ?
}

/*remove beginning http[s]，if start with “/”，concatecate it after domain*/
//FIXME, any possibility to coredump ??
char *patchlink(char *link, char *domain)
{
	int len1 = strlen(link);
	int len2 = strlen(domain);
	char *rect;
	int i;
	if (strncmp(link, "http", 4) == 0) {
		int llen;
		if (strncmp(link, "https", 5) == 0)
			llen = 8;
		else
			llen = 7;
		rect = (char *)malloc(len1 - llen + 1);
		for (i = 0; i < len1 - llen; ++i)
			rect[i] = link[i + llen];
		rect[len1 - llen] = '\0';
	} else if (strncmp(link, "/", 1) == 0) { // start with /
		rect = (char *)malloc(len1 + len2 + 1);
		for (i = 0; i < len2; ++i)
			rect[i] = domain[i];
		for (i = 0; i < len1; ++i)
			rect[i + len2] = link[i];
		rect[len1 + len2] = '\0';
		//printf("completion the url：|%s|\n",rect);
	} else { // unknown case
		return NULL;
	}

	return rect;
}

/*remove ending /, any link whose length is greater than MAX_LINK_LEN will be ignored and set link as NULL*/
void pretreatLink(char *link)
{
	if (link == NULL)
		return;
	//printf("before processing: link=%s\n",link);
	int len = strlen(link);
	if (link[len - 1] == '/')	/*removeing ending / */
		link[len - 1] = '\0';
	if (strlen(link) > MAX_LINK_LEN) {	/*set any hyper-link greater than 128 and set link as NULL */
		free(link);
		link = NULL;
	}
	//printf("after processing: link=%s\n",link);
}

/*Get depth in the hyper-link*/
int getDepth(char *link)
{
	int depth = 0;
	int len = strlen(link);
	int i;
	for (i = 0; i < len; ++i) {
		if (link[i] == '/')
			depth++;
	}
	return depth;
}

/*Get host and resource from link*/
void getHRfromlink(char *link, char *host, char *resource)
{
	//printf("link=%s\n",link);
	char *p = index(link, '/');
	//printf("p=%s\n",p);
	if (p == NULL) {
		strcpy(host, link);
		resource[0] = '/';
		resource[1] = '\0';
	} else {
		int dlen = p - link;
		int plen = strlen(link) - dlen;
		strncpy(host, link, dlen);
		host[dlen] = '\0';
		strcpy(resource, p);
		resource[plen] = '\0';
	}
	//printf("Get from link: host=%s\tresource=%s\n",host,resource);
}

/*Use url as file name，change slash to underline*/
char *link2fn(Url * arg)
{
	int l1 = strlen(arg->domain);
	int l2 = strlen(arg->path);
	char *filename;
	filename = (char *)calloc(l1 + l2 + 1, sizeof(char));
	int i = 0;
	for (; i < l1; ++i)
		filename[i] = arg->domain[i];
	for (i = 0; i < l2; ++i)
		filename[i + l1] = (arg->path[i] == '/' ? '_' : arg->path[i]);
	filename[l1 + l2] = '\0';
	return filename;
}

/**
 * @Function: string left shift until the last empty space to the beginning
 * @Return: num of chars left
 */
int leftshift(char *buf)
{
	char *p = rindex(buf, ' ');
	if (p == NULL) {	/*no empty space show up，clear buf，return 0 */
		memset(buf, 0x00, strlen(buf));
		return 0;
	} else {
		int leftlen = p - buf;
		int rightlen = strlen(buf) - leftlen;
		char *tmp = (char *)malloc(rightlen);
		strncpy(tmp, p, rightlen);
		memset(buf, 0x00, strlen(buf));
		strncpy(buf, tmp, rightlen);
		free(tmp);
		return rightlen;
	}
}

/**
 * @Function: extract all the hyper-link from string, and left shit all possible shortest hyper-link
 * @Return: num of chars left
 */
int extractLink(char *buf, char *domain)
{
	const char *regex = "href=\"[^ >]*\"";
	regex_t preg;
	const size_t nmatch = 10;
	regmatch_t pm[nmatch];
	if (regcomp(&preg, regex, 0) != 0) {// fail to compile regexp
		perror("regcomp");
		exit(1);
	}
	int z, i;
	z = regexec(&preg, buf, nmatch, pm, 0);
	if (z == REG_NOMATCH) {	/*no matched*/
		return leftshift(buf);
	} else {		/*matched*/
		char **links = (char **)calloc(nmatch, sizeof(char *));
		for (i = 0; i < nmatch && pm[i].rm_so != -1; ++i) {	/*extract all hyper-link*/
			int bpos = pm[i].rm_so + 6;
			int epos = pm[i].rm_eo - 2;
			int len = epos - bpos + 1;
			char *tmp;
			tmp = (char *)calloc(len + 1, 1);
			strncpy(tmp, buf + bpos, len);
			tmp[len] = '\0';
			//printf("raw link:|%s|\n",tmp);
			char *link = patchlink(tmp, domain);
			free(tmp);
			//printf("link after completion:|%s|\n",link);
			links[i] = link;
		}
		putlinks2queue(links, nmatch);
    // FIXME, no free again?? valgrind check it
		//free(links);
		return leftshift(buf + pm[nmatch - 1].rm_eo);
	}
}

#endif
