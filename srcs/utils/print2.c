/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:03:08 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/18 15:48:49 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

void	print_cmd_line_detail(t_parse **parse)
{
	int			i;
	int			type;
	const char	*e_type[] = {"CMD", "PIPE", "OR", "AND", "P_START", "P_END"};
	const char	*e_colors[] = {"\x1b[32m", "\x1b[33m", "\x1b[36m", "\x1b[34m",
		"\x1b[35m", "\x1b[31m"};

	i = -1;
	while (parse[++i])
	{
		ft_printf("\nnode %i:\t", i);
		type = parse[i]->type;
		if (type == CMD)
		{
			type = 0;
			ft_printf("%s%s\x1b[0m", e_colors[type], e_type[type]);
			print_node(parse[i]->cmd);
		}
		else
		{
			type -= 4;
			ft_printf("%s%s\x1b[0m\n", e_colors[type], e_type[type]);
		}
	}
}

void	print_cmd_line(t_parse **parse)
{
	int			i;
	const char	*e_type[] = {"CMD", "PIPE", "OR", "AND", "P_START", "P_END"};
	const char	*e_colors[] = {"\x1b[32m", "\x1b[33m", "\x1b[36m", "\x1b[34m",
		"\x1b[35m", "\x1b[31m"};
	int			type;

	i = -1;
	ft_printf("cmd_line:\n");
	while (parse[++i])
	{
		type = parse[i]->type;
		if (type == CMD)
			type = 0;
		if (type >= PIPE)
			type -= 4;
		ft_printf("%s%s\x1b[0m ", e_colors[type], e_type[type]);
	}
	ft_printf("\n\n");
}
