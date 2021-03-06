#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}
//modified for lab01
int
sys_exit(void)
{//Begins_update_for_LAB01_
int status
if (argint(0,&status) <0)
    return -1;
//end_update_for_LAB01
exit(status);
//if there is error, uncommented the line 24
return 0; // not reached
}

//modified for lab01
int
sys_wait(void)
{
    char *status;
    if(argptr(0,&status, sizeof(int))<0)
        return -1;
    return wait((int*)status);
}

//created for lab01
int
sys_waitpid(void)
{
    int pid;
    char *status;
    int options;
    if(argint(0,&pid)<0)
        return -1;
    if(argptr(1,&status, sizeof(int))<0)
        return -1;
    if(argint(2,&options)<0)
        return -1;

    return waitpid(pid,(int*)status,options);
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
