#ifndef _BLOOM_H
#define _BLOOM_H

#include<stdlib.h>
#include<assert.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<math.h>
#include<string.h>
#include<rpc/des_crypt.h>	/*for ecd_crypt */
#include<limits.h>		/*for INT_MAX */
#include<errno.h>
#include<string>
using namespace std;

#define MAX_URLPATH_NUM	1000000	/*maximum of url path(must be multiplies of 1000) */
#define MAX_URLDOMAIN_NUM	(MAX_URLPATH_NUM)/100	/*maximum of url domain(must be multiplies of 1000) */

//extern int stat(const char *path,struct stat *buf);
int d_table[MAX_URLDOMAIN_NUM] = { 0 };
int p_table[MAX_URLPATH_NUM] = { 0 };

pthread_mutex_t dtlock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t ptlock = PTHREAD_MUTEX_INITIALIZER;

int myEncrypt(char *str, char *key)
{
	assert(str != NULL);
	char *cipher = strdup(str);
	ecb_crypt(key, cipher, strlen(str), DES_ENCRYPT);	/*use ecb_crypt as 1st mapping*/
	int i;
	int var = 0;
	int len = strlen(cipher);
	for (i = 0; i < len; i++)
		var = (var * 7 + cipher[i]) % (int)INT_MAX;
	free(cipher);
	return var;
}

/*verdict domain exist or not，if not, record it into DomainBloomTable*/
int bloomDomain(char *domain)
{
	//printf("call bloomDomain\ndomain=%s\n",domain);
	int mod = 32 * MAX_URLDOMAIN_NUM;
	int flag = 0;
	string salt[] = { "Dm", "VB", "ui", "LK", "uj", "RD", "we", "fc" };
	int f[8] = { 0 };
	int g[8] = { 0 };
	int i;
	pthread_mutex_lock(&dtlock);
	for (i = 0; i < 8; i++) {
		char *key;
		key = strdup(salt[i].c_str());
		f[i] = myEncrypt(domain, key);
		free(key);
		srand(f[i]);
		g[i] = rand() % mod;
		int index = g[i] / 32; // map index
		int pos = g[i] % 32; // position inside the map entry
		if (d_table[index] & (0x80000000 >> pos))
			flag++;
		else
			d_table[index] |= (0x80000000 >> pos);
	}
	pthread_mutex_unlock(&dtlock);
	if (flag == 8) // use 8 bits to control
		return 1;	//return true if exist
	return 0;
}

//FIXME, why not template?
/*verdict path exist or not，if not, put it into PathBloomTable*/
int bloomPath(char *path)
{
	//printf("调用bloomPath\npath=%s\n",path);
	int mod = 32 * MAX_URLPATH_NUM;
	int flag = 0;
	string salt[] = { "Dm", "VB", "ui", "LK", "uj", "RD", "we", "fc" };
	int f[8] = { 0 };
	int g[8] = { 0 };
	int i;
	pthread_mutex_lock(&ptlock);
	for (i = 0; i < 8; i++) {
		char *key;
		key = strdup(salt[i].c_str());
		f[i] = myEncrypt(path, key);
		free(key);
		srand(f[i]);
		g[i] = rand() % mod;
		int index = g[i] / 32;
		int pos = g[i] % 32;
		if (p_table[index] & (0x80000000 >> pos))
			flag++;
		else
			p_table[index] |= (0x80000000 >> pos);
	}
	pthread_mutex_unlock(&ptlock);
	if (flag == 8)
		return 1;	
	return 0;
}

#endif
