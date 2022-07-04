#include "g_minishell.h"
#include "minishell.h"

void	cleanble_close_pipes(t_clean *cleanable)
{
	while (cleanable->n_pipes > 0)
		cleanable_pop_pipe(cleanable);
}
