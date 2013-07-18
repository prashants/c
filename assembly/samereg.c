/*
 * samereg - Use the same register for input and output
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

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int count = 0;

	printf("count before = %d\n", count);

	asm("INCL %0" : "=r"(count): "0"(count));
	asm("INCL %0" : "=r"(count): "0"(count));
	asm("INCL %0" : "=r"(count): "0"(count));
	asm("INCL %0" : "=r"(count): "0"(count));

	printf("count after  = %d\n", count);

	return 0;
}
