/*
 * directio - Read blocks using DIRECT IO mode 
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

#define _LARGEFILE64_SOURCE 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/fs.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/ioctl.h>

#define BLK_SIZE	4096
#define BUF_SIZE	10485760

// Compile command :
// $gcc -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 directio.c -o directio

int main(int argc, char *argv[])
{
	int fd = 0, disk = 0;
	int ret;
	int offset;
	unsigned long c = 0;
	int block_size, block_count, block_num;
	off64_t block_off, seek_ret;
	struct stat64 statinfo;
	struct timeval start_time, end_time;
	char *membuf = NULL;
	unsigned char *buf;

	//unsigned char buf[BLK_SIZE]  __attribute__ ((__aligned__ (BLK_SIZE)));
	//buf = (unsigned char *)memalign(BLK_SIZE, BLK_SIZE);
	//if (!buf) {
	//	fprintf(stderr, "failed to allocate memory\n");
	//	goto err;
	//}

	/* Allocate memory on page boundary */
	ret = posix_memalign((void **)&buf, BLK_SIZE, BLK_SIZE);
	if (ret != 0) {
		fprintf(stderr, "Failed to allocate memory\n");
		goto err;
	}

	if (argc != 3) {
		fprintf(stderr, "Invalid number of arguments\n"
				"Format  : $./directio <partition> <file>\n"
				"Example : $./directio /dev/sda1 ~/test.dump\n");
		goto err;
	}

	/* open partition */
	disk = open(argv[1], O_RDONLY | O_DIRECT | O_LARGEFILE);
	if (disk <= 0) {
		fprintf(stderr, "Cannot open partition %s\n", argv[1]);
		goto err;
	}

	/* open file */
	fd = open(argv[2], O_RDONLY | O_DIRECT | O_LARGEFILE);
	if (fd <= 0) {
		fprintf(stderr, "Cannot open file %s\n", argv[2]);
		goto err;
	}

	/* allocate buffer */
	membuf = malloc(BUF_SIZE);
	if (!membuf) {
		fprintf(stderr, "Failed to allocate memory\n");
		goto err;
	}

	/* get block size */
	if (ioctl(fd, FIGETBSZ, &block_size) < 0) {
		fprintf(stderr, "Failed to get block size\n");
		goto err;
	}

	/* get number of blocks of file */
	if (fstat64(fd, &statinfo) < 0) {
		fprintf(stderr, "Stat failed\n");
		goto err;
	}

	/* calculate number of blocks for the file */
	block_count = (statinfo.st_size + block_size - 1) / block_size;

	fprintf(stdout, "File : %s block_count = %d, block_size = %d\n",
			argv[2], block_count, block_size);

	offset = 0;
	gettimeofday(&start_time, 0);
	for (c = 0; c < block_count; c++) {
		/* get next block number allocated to file */
		block_num = c;
		if (ioctl(fd, FIBMAP, &block_num)) {
			fprintf(stderr, "IOCTL failed\n");
		}

		/* seek to the block directly on disk */
		block_off = (off64_t)block_num * (off64_t)block_size;
		seek_ret = lseek64(disk, block_off, SEEK_SET);
		if (seek_ret < 0) {
			fprintf(stderr, "Seek error at %lu - %lu\n",
					(unsigned long)block_off, (unsigned long)seek_ret);
			goto err;
		}

		/* read the block directly from disk */
		if (read(disk, buf, BLK_SIZE) != BLK_SIZE) {
			fprintf(stderr, "Read error at %lu\n",
					(long)block_off);
			goto err;
		}

		/* copy data to memory buffer of 10 MB */
		memcpy(membuf + offset, buf, BLK_SIZE);
		offset += 4096;
		if (offset >= BUF_SIZE) {
			printf("block_count = %lu / %d\n", c, block_count);
			offset = 0; /* reset buffer when end reached */
		}
	}
	gettimeofday(&end_time, 0);
	fprintf(stdout, "Time taken : %lu\n", end_time.tv_sec - start_time.tv_sec);

	return 0;

err:
	if (membuf)
		free(membuf);
	if (fd > 0)
		close(fd);
	if (disk > 0)
		close(disk);
	if (buf)
		free(buf);

	return -1;
}

