/*
 * disklist - List of disk and partitions using parted library
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
 *
 * Usage :
 * $sudo apt-get install libparted0-dev
 * $gcc disklist.c -o disklist -lparted
 * $sudo ./disklist
 */

#include <stdio.h>
#include <parted/parted.h>

typedef struct {
	unsigned char system;
} DosPartitionData;

int main()
{
	PedDevice *dev = NULL;
	PedDisk *disk = NULL;
	PedPartition *part = NULL;
	DosPartitionData *dos = NULL;
	char *type_name;

	ped_device_probe_all();

	/* Loop through each physical disk */
	while ((dev = ped_device_get_next (dev))) {
		printf("%s\n", dev->path);
		if (!ped_device_open(dev))
			continue;
		disk = ped_disk_new(dev);
		if (disk) {
			/* Loop through each disk partition */
			for (part = ped_disk_next_partition(disk, NULL); part;
					part = ped_disk_next_partition(disk, part)) {
				type_name = (char *)ped_partition_type_get_name(part->type);
				/* Check if its a primary or logical partition */
				if (part->type == 0 || part->type == 1) {
					dos = (DosPartitionData *)part->disk_specific;
					printf("num=%d type=%x fs_type=%s system=%x\n",
						part->num, part->type, type_name, dos->system);
				} else {
					printf("num=%d type=%x fs_type=%s\n",
						part->num, part->type, type_name);
				}
			}
			ped_disk_destroy(disk);
		}
	}
        exit(0);
}

