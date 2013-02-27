/*
 * fibmap - List blocks of a file
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
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/fs.h>
#include <assert.h>

int main(int argc, char **argv)
{
	int fd, i, block, blocksize, blkcnt;
	struct stat st;

	assert(argv[1] != NULL);

	fd = open(argv[1], O_RDONLY);
	if (fd <= 0) {
		perror("error opening file");
		goto end;
	}

	if (ioctl(fd, FIGETBSZ, &blocksize)) {
		perror("FIBMAP ioctl failed");
		goto end;
	}

	if (fstat(fd, &st)) {
		perror("fstat error");
		goto end;
	}

	blkcnt = (st.st_size + blocksize - 1) / blocksize;
	printf("File %s size %d blocks %d blocksize %d\n",
			argv[1], (int)st.st_size, blkcnt, blocksize);

	for (i = 0; i < blkcnt; i++) {
		block = i;
		if (ioctl(fd, FIBMAP, &block)) {
			perror("FIBMAP ioctl failed");
		}
		printf("%3d %10d\n", i, block);
	}

end:
	close(fd);
	return 0;
}

