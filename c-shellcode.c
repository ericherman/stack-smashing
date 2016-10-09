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
