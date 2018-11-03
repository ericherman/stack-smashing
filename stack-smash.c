/* stack-smash.c
   Copyright (C) 2014, 2018 Eric Herman <eric@freesa.org>

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
