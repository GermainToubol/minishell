#include <unistd.h>
#include "g_minishell.h"

static pid_t	_manage_last_pid(pid_t pid, int action)
{
	static pid_t	last_pid;

	if (action == 1)
		last_pid = pid;
	return (last_pid);
}

pid_t	get_last_pid(void)
{
	return (_manage_last_pid(0, 0));
}

void	set_last_pid(pid_t pid)
{
	_manage_last_pid(pid, 1);
}
