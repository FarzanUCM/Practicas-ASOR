#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <limits.h>

int main()
{	
	pid_t f = fork();
	
	if(f == 0)
	{
		pid_t sid = setsid();
		
		if(chdir("/tmp") == -1){
			perror("Error cambio de directorio: ");
			return -1;
		}

		pid_t pid = getpid();
		pid_t ppid = getppid();
		pid_t pgid = getpgid(pid);
		pgid = (pgid == 0) ? pid : pgid;

		
		struct rlimit rlim;
		getrlimit(RLIMIT_NOFILE, &rlim);
		
		char cwd[PATH_MAX];
		getcwd(cwd, PATH_MAX);

		printf("PID: %d\n"
			"PPID: %d\n"
			"PGID: %d\n"
			"SID: %d\n"
			"Max number of open files: %ld\n"
			"Current working directory: %s\n",
			pid, ppid, pgid, sid, rlim.rlim_max, cwd);
	}
	else if(f == -1){
		perror("Error fork: ");
		return -1;
	}
	else
	{
		sleep(1);
	}

	return 0;
}
