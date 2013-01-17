/*
 * fwrite - Write to a file
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

int main(int argc, char *argv[])
{
	FILE *f;
	char str[] = "Hello World";

	f = fopen("./test.txt", "w");
	if (!f) {
		perror("Error opening file");
		exit(1);
	}

	/* reduce size of str by 1 to remove \0 */
	fwrite(str, sizeof(str) - 1, 1, f);

	fclose(f);
	return 0;
}

