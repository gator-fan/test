#ifndef __BLOOMFILTER_H__
#define __BLOOMFILTER_H__

#include<stdio.h>
#include<stdlib.h>

typedef struct {
unsigned int size;
unsigned int *filter;
/*other fields*/
}BF;

BF* bloom_create();
int bloom_destroy(BF **bfArray);
int bloom_add(BF **bfArray,char *str);
int bloom_check(BF **bfArray,char *str);
void bloom(FILE *pool,FILE *check, FILE *result);

#endif
