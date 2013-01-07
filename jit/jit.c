/*
 * jit -Small jit compiler
 *
 * Written in 2012 by Prashant P Shah <pshah.mumbai@gmail.com>
 *
 * To the extent possible under law, the author(s) have dedicated
 * all copyright and related and neighboring rights to this software
 * to the public domain worldwide. This software is distributed
 * without any warranty.
 *
 * You should have received a copy of the CC0 Public Domain Dedication
 * along with this software.
 * If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
 */

/**
 * Run as :
 * $./jit 40
 * $echo $?
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

int main(int argc, char *argv[])
{
	/* Machine code for : mov eax, 0; ret */
	unsigned char code[] = {0xb8, 0x00, 0x00, 0x00, 0x00, 0xc3};
	if (argc < 2) {
		fprintf(stderr, "Usage: jit <integer>\n");
		return 1;
	}

	/* Overwrite immediate value "0" in the instruction with the users value
	 * Final code : mov eax, <user value>; ret
	 */
	int num = atoi(argv[1]);
	memcpy(&code[1], &num, 4);

	/* Allocate writable and executable memory - high risk */
	void *mem = mmap(NULL, sizeof(code), PROT_WRITE|PROT_EXEC, MAP_ANON|MAP_PRIVATE, -1, 0);
	memcpy(mem, code, sizeof(code));

	/* This function will return the user's value
	 * func() is a function pointer that points to start of the mmap memory
	 */
	int (*func)() = mem;
	int ret = func();
	fprintf(stdout, "Returned : %d\n", ret);

	return 0;
}

