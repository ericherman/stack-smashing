#include <stdio.h>
#include <string.h>

#define BUFSIZE 32

int main(int argc, char *argv[])
{
	char before;
	char buf[BUFSIZE];
	char after;

	if (argc < 2) {
		fprintf(stderr, "%s 'string to fill %d character buffer'\n",
			argv[0], BUFSIZE);
		return -1;
	}
	before = '.';
	after = '.';

	strcpy(buf, argv[1]);

	printf("before='%c', after='%c'\n", before, after);
	printf("buf=\"%s\"\n", buf);

	return 0;
}
