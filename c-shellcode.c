#include <unistd.h>

int main()
{
	char *name[2];
	name[0] = "/bin/sh";
	name[1] = NULL;

	execve(name[0], name, 0);

	return 0;
}
