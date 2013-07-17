/*
 * printconst - Read a constant and print it 
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

int main(int argc, char *argv[])
{
	int val = 0;
	asm("MOV $100, %0" : "=r"(val));
	printf("val = %d\n", val);
	return 0;
}
