#include <limits.h>
#include "g_minishell.h"

static int	ft_isspace(char c);

long long	ft_atoll_protected(char *s)
{
	long long	n;
	int			minus;

	n = 0;
	minus = 1;
	while (ft_isspace(*s) == 1)
		s++;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			minus = -1;
		s++;
	}
	while (ft_isdigit(*s))
	{
		if (minus > 0 && (LLONG_MAX - *s + '0') / 10 < n)
			return (0);
		if (minus < 0 && (LLONG_MIN + *s - '0') / 10 > -n)
			return (0);
		n = 10 * n + *s - '0';
		s++;
	}
	return (n * minus);
}

static int	ft_isspace(char c)
{
	if (c == ' ')
		return (1);
	if (c >= 9 && c <= 13)
		return (1);
	return (0);
}
