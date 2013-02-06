/*
 * namespace - Namespace demo 
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

#define _GNU_SOURCE
#include <sys/utsname.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sched.h>
#include <signal.h>
#include <wait.h>

#define STACK_SIZE 4096

static char child_stack[STACK_SIZE];

static char newhostname[] = "rambo";

/* Child function */
static int childFunc(void *arg)
{
	struct utsname uts;

	/* Change the hostname in chid namespace */
	if (sethostname(newhostname, sizeof(newhostname)) == -1) {
		perror("sethostname in child");
		return 0;
	}

	/* Read the hostname in child process */
	if (uname(&uts) == -1) {
		perror("uname child");
		return 0;
	}

	printf("hostname in child: %s\n", uts.nodename);

	return 0;
}

int main(int argc, char *argv[])
{
	struct utsname uts;
	pid_t child_pid;

	/* Create a child process */
	child_pid = clone(childFunc, child_stack + STACK_SIZE,
			CLONE_NEWUTS | SIGCHLD, &newhostname);

	/* Check if clone() succeded */
	if (child_pid == -1) {
		perror("clone");
		exit(EXIT_FAILURE);
	}
	printf("PID of child created by clone is %ld\n", (long)child_pid);

	sleep(10);

	/* Read the hostname of parent process */
	if (uname(&uts) == -1) {
		perror("uname parent");
		exit(EXIT_FAILURE);
	}

	printf("hostname in parent: %s\n", uts.nodename);

	/* Wait for child */
	if (waitpid(child_pid, NULL, 0) == -1) {
		perror("wait for child");
		exit(EXIT_FAILURE);
	}

	printf("child has terminated\n");

	exit(EXIT_SUCCESS);
}

