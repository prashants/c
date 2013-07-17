/*
 * regmath - Register maths - add, subtract, multiply 
 *
 * Written in 2013 by Prashant P Shah <pshah.mumbai@gmail.com>
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

// Note : Use GDB to inspect value of registers
// gcc -g -Wall regmath.c -o regmath
// gdb regmath
// break <line-number>
// run
// info registers
// print $rax

#include <stdio.h>

int main(int argc, char *argv[])
{
	/* Copying */
	asm("MOVL $5, %eax");
	asm("MOVL %eax, %ebx");

	/* Addition - save result in %eax */
	asm("MOVL $10, %eax");
	asm("MOVL $20, %ebx");
	asm("ADDL %ebx, %eax");

	/* Subtract - save result in %eax */
	asm("MOVL $200, %eax");
	asm("MOVL $25, %ebx");
	asm("SUBL %ebx, %eax");

	/* Multiply - save result in %eax */
	asm("MOVL $20, %eax");
	asm("MOVL $30, %ebx");
	asm("IMULL %ebx, %eax");

	return 0;
}
