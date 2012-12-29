/*
 * reversebits - Reverse or mirror the bits of a byte using a table
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
#include <stdlib.h>

unsigned char revtable[256];

void bitdump(unsigned char data)
{
	int c = 0;
	for (c = 0; c < 8; c++) {
		if ((data & 0x80) == 0) {
			printf("%d", 0);
		} else {
			printf("%d", 1);
		}
		data <<= 1;
	}
}

unsigned char reversebit(unsigned char data)
{
	unsigned char retdata = 0;
	int c = 0;
	for (c = 0; c < 8; c++) {
		if ((data & (1 << c)) == 0) {
			/* Skip */
		} else {
			retdata = retdata | (0x80 >> c);
		}
	}
	return retdata;
}

int main(int argc, char *argv[])
{
	int c = 0;
	for (c = 0; c < sizeof(revtable); c++) {
		revtable[c] = c; 
	}
	for (c = 0; c < sizeof(revtable); c++) {
		printf("%03d = ", c);
		bitdump(revtable[c]);
		revtable[c] = reversebit(revtable[c]);
		printf(" ====> ");
		printf("%03d = ", c);
		bitdump(revtable[c]);
		printf(" = %03d", revtable[c]);
		printf("\n");
	}
	return EXIT_SUCCESS;
}

