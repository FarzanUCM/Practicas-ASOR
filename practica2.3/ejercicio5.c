#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <limits.h>

int main()
{
	pid_t pid = getpid();
	pid_t ppid = getppid();
	pid_t pgid = getpgid(pid);
	pgid = (pgid == 0) ? pid : pgid;

	pid_t sid = getsid(pid);
	
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

	return 0;
}
