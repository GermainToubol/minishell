#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"
#include "g_minishell.h"

static int	_add_pid(pid_t pid, t_list **pid_list)
{
	new = ft_lstnew((long)pid);
	if (new == NULL)
	{
		ft_fprintf(2, "minishell: Memory allocation error");
		ft_lstclear(&pid_list, NULL);
		return (1);
	}
	ft_lstadd_front(&pid_list, new);
	if (pid_list == NULL)
	{
		ft_fprintf(2, "minishell: Memory allocation error");
		return (1);
	}
	return (0);
}

static int	_remove_pid(pid_t pid, t_list **pid_list)
{
	t_list	*prev;
	t_list	*tmp;

	prev = NULL;
	tmp = *pid_list;
	while (tmp != NULL)
	{
		if ((long)tmp->content == (long)pid)
		{
			if (prev == NULL)
				*pid_list = tmp->next;
			else
				prev->next = tmp->next;
			ft_lstdelone(tmp, NULL);
			return (0);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (0);
}

static int	_signal_all(t_list	*pid_list)
{
	t_list	*tmp;
	pid_t	pid;

	tmp = pid_list;

}

int	manage_pid_list(pid_t pid, int action)
{
	static	t_list	*pid_list;
	t_list			*new;

	if (action == 1)
		return (_add_pid(pid, &pid_list));
	if (action == -1)
		return (_remove_pid(pid, &pid_list));
	if (action == 2)
		return (_signal_all(pid_list));
	return (0);
}
