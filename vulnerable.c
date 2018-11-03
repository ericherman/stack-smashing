/* vulnerable.c
   Copyright (C) 2015, 2016, 2018 Eric Herman <eric@freesa.org>

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
/*
* vulnerable.c : a program intentially written with a buffer over-flow bug
*/

#include <stdio.h>
#include <string.h>

#define BUFSIZE 32
#define BUFSIZE1 1024

#if _POSIX_C_SOURCE < 200809L
size_t strnlen(const char *str, size_t buf_size)
{
	size_t len = strlen(str);
	if (len > buf_size) {
		return buf_size;
	}
	return len;
}
#endif

void fgets_and_chomp(char *buf, size_t len)
{
	size_t strlen;

	if (fgets(buf, len, stdin)) {
		strlen = strnlen(buf, len);
		fprintf(stderr, "%0x\n", (unsigned int)buf);
		if (strlen) {
			buf[strlen - 1] = '\0';
		}
	}
}

char vulnerable(void)
{
	char buf[BUFSIZE];	/* SHORT BUF */

	printf("What is your name? ");
	fgets_and_chomp(buf, BUFSIZE1);	/* LONG BUF */
	printf("Hello, %s!\n", buf);
	return buf[0];
}

int main(void)
{
	char buf1[BUFSIZE1];
	buf1[BUFSIZE1 - 1] = vulnerable();
	return buf1[BUFSIZE1 - 1] != 0;
}
