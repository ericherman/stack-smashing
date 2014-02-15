/* modified from "Smashing The Stack For Fun And Profit" example 3 */
/* see: http://insecure.org/stf/smashstack.html */

#include <stdio.h>

void func(char skip_size, char bytes_back, char debug)
{
	char buffer1[5];
	char buffer2[10];
	size_t *return_addr;

	return_addr = (size_t *) ((char *)(buffer1 + bytes_back));
	if (debug) {
		printf("buffer1: %p\n", (void *)buffer1);
		printf("buffer2: %p\n", (void *)buffer2);
		printf("return addr may be %p\n", (void *)return_addr);
		printf("\tbytes_back=%d,skip_size=%d\n", bytes_back, skip_size);
	}
	(*return_addr) += skip_size;
}

int main(int argc, char *argv[])
{
	int x;
	char skip_size;
	char bytes_back;
	int debug;
	debug = (argc > 1) ? 1 : 0;
	if (debug) {
		printf("treating %s as debug\n", argv[1]);
	}

	skip_size = 8;
	bytes_back = 20;

	if (debug) {
		printf("skip_size=%d\n", skip_size);
	}
	x = 0;
	func(skip_size, bytes_back, debug);
	x = 1;
	if (debug) {
		printf("x == %d\n", x);
	}
	if (x == 0) {
		printf("skipped assignment to x!\n");
		return 0;
	}

	printf("Cound not skip assignment to 'x'\n");
	return 1;
}
