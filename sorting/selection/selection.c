/*
 * seletion - Selection sort an array of integers
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

#define ARRAY_SIZE	1000

int main(int argc, char *argv[])
{
	int data[ARRAY_SIZE]; /* input array to be sorted */
	int c, temp;
	int smallest, head;

	/* filling input data with random values between 0 to 10,000 */
	for (c = 0; c < ARRAY_SIZE; c++) {
		data[c] = rand() % 10000;
	}

	/*
	 * 'head' is the start element from where to begin the search for location of smallest element
	 * we start from 0 and after every iteraion of inner for loop we swap the smallest element with
	 * the head and move the head to the next element
	 */
	for (head = 0; head < ARRAY_SIZE; head++) {
		/* loop through all elements starting from head and find the index of the smallest element */
		for (c = head, smallest = head; c < ARRAY_SIZE; c++) {
			if (data[c] < data[smallest]) {
				smallest = c;
			}
		}
		/* 'smallest' has the index of the smallest element, swap it with the head element */
		temp = data[head];
		data[head] = data[smallest];
		data[smallest] = temp;
	}

	/* print sorted data */
	for (c = 0; c < ARRAY_SIZE; c++) {
		printf("%d\n", data[c]);
	}

	return 0;
}

