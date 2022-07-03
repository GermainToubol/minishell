#include "g_minishell.h"

static int	_interupted_status(int action)
{
	static int	_interupted = 0;

	if (action == 1)
		_interupted = 1;
	if (action == -1)
		_interupted = 0;
	return (_interupted);
}

void	set_interupt(void)
{
	_interupted_status(1);
}

void	reset_interupt(void)
{
	_interupted_status(-1);
}

int	is_interupted(void)
{
	return (_interupted_status(0));
}
