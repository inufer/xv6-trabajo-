#include "types.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "x86.h"
#include "syscall.h"


// User code makes a system call with INT T_SYSCALL.
// System call number in %eax.
// Arguments on the stack, from the user call to the C
// library system call function. The saved user %esp points
// to a saved program counter, and then the first argument.

// Fetch the int at addr from the current process.
int
fetchint(uint addr, int *ip)
{
  struct proc *curproc = myproc();

  if(addr >= curproc->sz || addr+4 > curproc->sz)
    return -1;
  *ip = *(int*)(addr);
  return 0;
}

// Fetch the nul-terminated string at addr from the current process.
// Doesn't actually copy the string - just sets *pp to point at it.
// Returns length of string, not including nul.
int
fetchstr(uint addr, char **pp)
{
  char *s, *ep;
  struct proc *curproc = myproc();

  if(addr >= curproc->sz)
    return -1;
  *pp = (char*)addr;
  ep = (char*)curproc->sz;
  for(s = *pp; s < ep; s++){
    if(*s == 0)
      return s - *pp;
  }
  return -1;
}

// Fetch the nth 32-bit system call argument.
int
argint(int n, int *ip)
{
  return fetchint((myproc()->tf->esp) + 4 + 4*n, ip);
}

// Fetch the nth word-sized system call argument as a pointer
// to a block of memory of size bytes.  Check that the pointer
// lies within the process address space.
int
argptr(int n, char **pp, int size)
{
  int i;
  struct proc *curproc = myproc();
 
  if(argint(n, &i) < 0)
    return -1;
  if(size < 0 || (uint)i >= curproc->sz || (uint)i+size > curproc->sz)
    return -1;
  *pp = (char*)i;
  return 0;
}

// Fetch the nth word-sized system call argument as a string pointer.
// Check that the pointer is valid and the string is nul-terminated.
// (There is no shared writable memory, so the string can't change
// between this check and being used by the kernel.)
int
argstr(int n, char **pp)
{
  int addr;
  if(argint(n, &addr) < 0)
    return -1;
  return fetchstr(addr, pp);
}

extern int syschdir;
extern int sysclose;
extern int sysdup;
extern int sysexec;
extern int sysexit;  
extern int sysfork;
extern int sysfstat;
extern int sysgetpid;
extern int syskill;
extern int syslink;
extern int sysmkdir;
extern int sysmknod;
extern int sysopen;
extern int syspipe;
extern int sysread;
extern int syssbrk;
extern int syssleep;    
extern int sysunlink;
extern int syswait;
extern int syswrite;
extern int sysuptime;
extern int syscps;                                        
extern int syscsc;
extern int sysdate;
extern int syscount;

extern int sys_chdir(void);
extern int sys_close(void);
extern int sys_dup(void);
extern int sys_exec(void);
extern int sys_exit(void);
extern int sys_fork(void);
extern int sys_fstat(void);
extern int sys_getpid(void);
extern int sys_kill(void);
extern int sys_link(void);
extern int sys_mkdir(void);
extern int sys_mknod(void);
extern int sys_open(void);
extern int sys_pipe(void);
extern int sys_read(void);
extern int sys_sbrk(void);
extern int sys_sleep(void);
extern int sys_unlink(void);
extern int sys_wait(void);
extern int sys_write(void);
extern int sys_uptime(void);
extern int sys_cps(void);
extern int sys_csc(void);
extern int sys_date(void);
extern int sys_count(void);

static int (*syscalls[])(void) = {
[SYS_fork]    sys_fork,
[SYS_exit]    sys_exit,
[SYS_wait]    sys_wait,
[SYS_pipe]    sys_pipe,
[SYS_read]    sys_read,
[SYS_kill]    sys_kill,
[SYS_exec]    sys_exec,
[SYS_fstat]   sys_fstat,
[SYS_chdir]   sys_chdir,
[SYS_dup]     sys_dup,
[SYS_getpid]  sys_getpid,
[SYS_sbrk]    sys_sbrk,
[SYS_sleep]   sys_sleep,
[SYS_uptime]  sys_uptime,
[SYS_open]    sys_open,
[SYS_write]   sys_write,
[SYS_mknod]   sys_mknod,
[SYS_unlink]  sys_unlink,
[SYS_link]    sys_link,
[SYS_mkdir]   sys_mkdir,
[SYS_close]   sys_close,
[SYS_cps]     sys_cps,
[SYS_csc]     sys_csc,
[SYS_date]    sys_date,
[SYS_count] sys_count,
};

char* syscls_names[24] =
{
 "fork",
 "exit",
 "wait",
 "pipe",
 "read",
 "kill",
 "exec",
 "fstat",
 "chdir",
 "dup",
 "getpid",
 "sbrk",
 "sleep",
 "uptime",
 "open",
 "write",
 "mknod",
 "unlink",
 "link",
 "mkdir",
 "close",
 "cps",
 "csc"
 "date",
"counter",
};





int cont = 0; 

void
syscall(void)
{ 

  if(cont==0)
{
     //Initialize
     for(int i =0; i<sizeof(syscls)/sizeof(syscls[0]);i++)
        syscls[i]=0;
        cont++;
}
  int num;
  struct proc *curproc = myproc();

  num = curproc->tf->eax;
  syscls[num-1]++;//cont
  if(num == 1){
    syschdir++;
  }else if(num == 2){
    sysclose++;
  }else if(num == 3){
    sysdup++;
  }else if(num == 4){
    sysexec++;
  }else if(num == 5){
    sysexit++;
  }else if(num == 6){
    sysfork++;        
  }else if(num == 7){
    sysfstat++;       
  }else if(num == 8){
    sysgetpid++;        
  }else if(num == 9){
    syskill++;       
  }else if(num == 10){
    syslink++;       
  }else if(num == 11){
    sysmkdir++;       
  }else if(num == 12){
    sysmknod++;
  }else if(num == 13){
    sysopen++;       
  }else if(num == 14){
    syspipe++;       
  }else if(num == 15){
    sysread++;       
  }else if(num == 16){
    syssbrk++;      
  }else if(num == 17){
    syssleep++;       
  }else if(num == 18){
    sysunlink++;
  }else if(num == 19){
    syswait++;       
  }else if(num == 20){
    syswrite++;      
  }else if(num == 21){
    sysuptime++; 
  }else if(num == 22){
    syscps++;
  }else if(num == 23){
    syscsc++;}
   else if(num == 24){                                  
    sysdate++;  
    }else if(num == 25){                                               
    syscount++;            
  }








  if(num > 0 && num < NELEM(syscalls) && syscalls[num]) {
    curproc->tf->eax = syscalls[num]();
  } else {
    cprintf("%d %s: unknown sys call %d\n",
            curproc->pid, curproc->name, num);
    curproc->tf->eax = -1;
  }
}
