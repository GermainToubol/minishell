/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 17:34:19 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/22 13:49:56 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include "expand.h"
#include "utils.h"

char	**new_tab(const char **av, int size)
{
	char	**ret;
	int		i;

	ret = ft_calloc(size, sizeof(char *));
	if (!ret)
		return (NULL);
	i = 0;
	while (++i < size)
	{
		ret[i - 1] = ft_strdup(av[i]);
		if (!ret[i - 1])
			return (free_tab(ret), NULL);
	}
	ret[i - 1] = NULL;
	return (ret);
}

int	main(int ac, const char **av)
{
	char	**lst;
	char	**new;
	size_t	i;

	if (ac < 2)
		return (display_error("Error\nusage: ./wildcard [path]\n", 0), 1);
	ft_printf("\x1b[32mWelcome to wildcard\n\x1b[0m");
	lst = new_tab(av, ac);
	if (!lst)
		return (1);
	new = do_expand(lst);
	free_tab(lst);
	if (!new)
		return (display_error("Error\n", 0), 1);
	i = 0;
	while (new[i])
	{
		ft_printf("%i : %s\n", i, new[i]);
		i++;
	}
	free_tab(new);
	return (0);
}
