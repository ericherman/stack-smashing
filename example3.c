/* example3.c
   Copyright (C) 2014, 2015, 2018 Eric Herman <eric@freesa.org>

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

	https://www.gnu.org/licenses/gpl-3.0.txt
 */
/* modified from "Smashing The Stack For Fun And Profit" example 3 */
/* see: http://insecure.org/stf/smashstack.html */

#include <stdio.h>
#include <stdlib.h>

#if __GNUC__
  #if __x86_64__ || __ppc64__
    #define DEFAULT_SKIP_SIZE 1
    #define DEFAULT_BYTES_BACK 24
  #else
    #define DEFAULT_SKIP_SIZE 8
    #define DEFAULT_BYTES_BACK 21
  #endif
#endif

void func(char skip_size, char bytes_back, char debug)
{
	char buffer1[5];
	char buffer2[10];
	char *return_addr;

	return_addr = buffer1 + bytes_back;
	if (debug) {
		printf("buffer1: %p\n", (void *)buffer1);
		printf("buffer2: %p\n", (void *)buffer2);
		printf("return addr may be %p\n", (void *)return_addr);
		printf("\tbytes_back=%d,skip_size=%d\n", bytes_back, skip_size);
	}
	(*return_addr) += skip_size;
	if (debug) {
		printf("return addr now is %p\n", (void *)return_addr);
	}
}

int main(int argc, char *argv[])
{
	int x;
	char skip_size;
	char bytes_back;
	char debug;

	debug = (argc > 3) ? atoi(argv[3]) : 0;
	skip_size = (argc > 2) ? atoi(argv[2]) : DEFAULT_SKIP_SIZE;
	bytes_back = (argc > 1) ? atoi(argv[1]) : DEFAULT_BYTES_BACK;

	if (debug) {
		printf("skip_size=%d\n", skip_size);
		printf("bytes_back=%d\n", bytes_back);
	}

	x = 0;
	func(skip_size, bytes_back, debug);
	x = 1;

	if (debug) {
		printf("x == %d\n", x);
	}
	if (x == 0) {
		printf("skip_size=%d\n", skip_size);
		printf("bytes_back=%d\n", bytes_back);
		printf("skipped assignment to x!\n");
		return 0;
	}

	printf("did not skip assignment to 'x'\n");
	return 1;
}
