#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/prctl.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	if(argc < 2)
	{
		fprintf(stderr, "A process to execute is required\n");
		return 1;
	}

	int ret = prctl(PR_SET_MEMORY_MERGE, 1, 0, 0, 0);
	if(ret != 0)
	{
		fprintf(stderr, "Unable to enable KSM for process: %s\n", strerror(errno));
		return 2;
	}

	printf("PR_SET_MEMORY_MERGE set to %u\n", prctl(PR_GET_MEMORY_MERGE, 0, 0, 0, 0));

	pid_t parent_pid = getpid();
	pid_t pid = fork();
	if(pid == 0)
	{
		printf("PR_SET_MEMORY_MERGE in child is %u\n", prctl(PR_GET_MEMORY_MERGE, 0, 0, 0, 0));
		execvp(argv[1], argv+1);
		fprintf(stderr, "Unable exec process: %s\n", strerror(errno));
		return 3;
	}
	else if(pid == -1)
	{
		fprintf(stderr, "Unable fork: %s\n", strerror(errno));
	}
	else if(pid == -1)
	{
		waitpid(pid, NULL, 0);
	}
	return 0;
}

