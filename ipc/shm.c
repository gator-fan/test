/*************************************************************************
 * @File Name: shm.c
 * @Author: wangfan
 * @Mail: wangfan@mvad.com 
 * @Created Time: 2015年08月13日 星期四 14时34分56秒
 ************************************************************************/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <stdlib.h>

#define IPCKEY 0x366378

typedef struct {
  char agen[10];
  unsigned char file_no;
} st_setting;

int main(int argc, char**argv)
{
    int shm_id;
    key_t key;
    st_setting* p_setting;

    shm_id = shmget(IPCKEY, 1028, 0640);
    if(shm_id != -1)
    {
      p_setting = (st_setting*) shmat(shm_id, NULL, 0);
      if(p_setting != (void*) -1)
      {
        shmdt(p_setting);
        shmctl(shm_id, IPC_RMID, 0);
      }
    }

    shm_id = shmget(IPCKEY, 1028, 0640|IPC_CREAT|IPC_EXCL);
    if(shm_id == -1)
    {
      printf("shmget error\n");
      return -1;
    }
    p_setting = (st_setting*)shmat(shm_id, NULL, 0);
    strncpy(p_setting->agen, "wangfan", 10);
    printf("agen: %s\n", p_setting->agen);

    p_setting->file_no = 1;
    printf("file_no:%d\n", p_setting->file_no);

    system("ipcs -m");

    if(shmdt(p_setting) == -1)
      perror("detach error");

    system("ipcs -m");

    if(shmctl(shm_id, IPC_RMID, NULL) == -1)
      perror("delete error");

    return 0;
}
