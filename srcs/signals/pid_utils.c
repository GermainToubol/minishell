#include <unistd.h>
#include "minishell.h"
#include "g_minishell.h"

int	pid_extend_list(pid_t pid)
{
	return (manage_pid_list(pid, 1));
}

int	pid_signal_all(void)
{
	return (manage_pid_list(0, 2));
}

int	pid_clear_list(void)
{
	return (manage_pid_list(0, -2));
}

int	pid_remove_pid(pid_t pid)
{
	return (manage_pid_list(pid, -1));
}

int	pid_lstlen(void)
{
	return (manage_pid_list(0, 3));
}
