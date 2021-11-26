#include <sys/types.h>
#include <unistd.h>
#include <sched.h>
#include <errno.h>
#include <stdio.h>

int main()
{
	pid_t pid = getpid();
	int sched = sched_getscheduler(pid);
	if(sched == -1)
	{
		perror("Error en scheduler: ");
		return -1;
	}

	switch(sched)
	{
		case SCHED_FIFO:
			printf("SCHED_FIFO policy\n");
			break;
		case SCHED_OTHER:
			printf("SCHED_OTHER policy\n");
			break;
		case SCHED_RR:
			printf("SCHED_RR policy\n");
			break;
	}
	
	struct sched_param p;
	sched_getparam(pid, &p);
	
	printf("Priority: %d\n", p.sched_priority);
	printf("Max priority value: %d\n", sched_get_priority_max(sched));
	printf("Min priority value: %d\n", sched_get_priority_min(sched));
}

