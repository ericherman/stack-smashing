/* c-shellcode.c
   Copyright (C) 2014, 2016, 2018 Eric Herman <eric@freesa.org>

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
int execve(const char *filename, char *const argv[], char *const envp[]);

int main()
{
	char *name[2];
	unsigned int vals[2];

	vals[0] = 'nib/';
	vals[1] = '\0hs/';

	name[0] = (char *)vals;
	name[1] = 0;

	execve(name[0], name, 0);

	return 0;
}
