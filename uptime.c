#include "types.h"
#include "user.h"

int
main (int argc, char *argv[])
{
	int utime;
	utime = uptime();
	printf(1, "up %d ticks\n", utime);
	exit();
}
