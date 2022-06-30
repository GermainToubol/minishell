/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_hdoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 23:56:07 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/30 12:44:42 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include "lexer.h"
#include "expand.h"

int	main(int ac, char **av, char **envp)
{
	char	*file;
	int		i;
	int		fd;

	if (ac <= 1)
		return (0);
	i = 1;
	fd = 0;
	while (i < ac)
	{
		file = ft_strdup(av[i]);
		if (set_hdoc(&file))
			return (free(file), 1);
		if (get_hdoc(file, fd, envp) == -1)
			return (free(file), 1);
		free(file);
		i++;
	}
	close(fd);
	return (0);
}
