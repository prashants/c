/*
 * screenmsg - Print a message to terminal
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
	char *msg = "Hello world from assembly\n";

	// http://asm.sourceforge.net/syscall.html#p33
	// http://jakash3.wordpress.com/2010/10/14/linux-assembly/

	asm("MOVL $4, %eax");		// system call code for write
	asm("MOVL $1, %ebx");		// file descriptor = stdout (1)
	asm("MOVL %0, %%ecx" : : "m"(msg));	// pointer to buffer
	asm("MOVL $26, %edx");		// size of buffer
	asm("INT $0x80");		// software interrrupt to system call

	return 0;
}
