#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{

const char *namesyscalls[] = {
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
"close"	,
"cps"
"csc"
"date"
"count",
	};




 int nsyscall = -1;
 if (argc == 2) {
  nsyscall = atoi(argv[1]);
 }
 if (nsyscall == -1) {
  // mostrar todas las llamadas al sistema
  // con su correspondiente numero de invocaciones
	for(int i = 0; i < 26;)
	{
	printf(1, "%s ---> %d \n", namesyscalls[i], count(i));
	}


 } else {
  // mostrar la llamada al sistema dada en nsyscall
  // con su correspondiente numero de invocaciones
	printf(1, "%s ---> %d \n", namesyscalls[nsyscall], count(nsyscall));
 }
 exit();
}
