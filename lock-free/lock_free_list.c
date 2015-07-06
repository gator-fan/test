/*************************************************************************
 * @File Name: lock_free_list.c
 * @Author: wangfan
 * @Mail: wangfan@mvad.com 
 * @Created Time: 2015年07月02日 星期四 10时09分24秒
 ************************************************************************/

#include <stdio.h>

struct node_t{
  key_t key;
  value_t val;
  node_t *next;
};

int l_find(node_t **pred_ptr, node_t **item_ptr, node_t *head, key_t key)
{
  node_t *pred = head;
  node_t *item = head->next;
  while(item)
  {
    int d = KEY_CMP(item->key, key);
    if(d >= 0)
    {
      *pred_ptr = pred;
      *item_ptr = item;
      return d == 0 ? TRUE: FALSE;
    }
    pred = item;
    item = item->next;
  }
  *pred_ptr = pred;
  *item_ptr = NULL;
  return FALSE;
}

int l_insert(node_t *head, key_t key, value_t val)
{
  node_t *pred, *item, *new_item;
  while(TRUE){
    if(l_find(&pred, &item, head, key))
    {
      return FALSE;
    }
    new_item = (node_t*) malloc(sizeof(node_t));
    new_item->key = key;
    new_item->val = val;
    new_item->next = item;
    if(CAS(&pred->next, item, new_item)){
      return TRUE;
    }
    free(new_item);
  }
}
