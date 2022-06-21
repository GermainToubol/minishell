/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 17:34:19 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/21 18:04:44 by fmauguin         ###   ########.fr       */
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
	size_t	i;

	if (ac < 2)
		return (display_error("Error\nusage: ./wildcard [path]\n", 0), 1);
	ft_printf("\x1b[32mWelcome to wildcard\n\x1b[0m");
	lst = new_tab(av, ac);
	if (!lst)
		return (1);
	lst = do_expand(lst);
	if (!lst)
		return (display_error("Error\n", 0), 1);
	i = 0;
	while (lst[i])
	{
		ft_printf("%i : %s\n", i, lst[i]);
		i++;
	}
	free_tab(lst);
	return (0);
}
