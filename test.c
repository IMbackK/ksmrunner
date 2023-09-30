#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/prctl.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	int merge = prctl(PR_GET_MEMORY_MERGE, 0, 0, 0, 0);
	printf("PR_SET_MEMORY_MERGE is %u after exec\n", merge);

	if(merge != 1)
	{
		fprintf(stderr, "KSM merging not enabled!\n");
		return 1;
	}

	printf("allocating memory\n");
	char* buf = malloc(100000000);

	printf("writeing memory\n");
	for(size_t i = 0; i < 100000000; i++)
		buf[i] = 0x44;

	printf("reading memory\n");
	volatile char read;
	while(true)
	{
		for(size_t i = 0; i < 100000000; i++)
		{
			read = buf[i];
			if(read != 0x44)
				return 2;
		}
		sleep(1);
	}
	return 0;
}
