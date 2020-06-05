#include "types.h"
#include "user.h"

int
main (int argc, char *argv[])
{
	int utime;
	utime = (60*uptime()/atoi(argv[1]));
	printf(1, "up %d ticks\n", utime);
	exit();
}
