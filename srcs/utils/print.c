/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:11:19 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/04 01:11:48 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	print_tokens(t_tokens *tokens)
{
	size_t	i;

	i = 0;
	while (i < tokens->size)
	{
		ft_printf("\nElement: %i\n", i);
		ft_printf("data: %s\n", tokens->tokens[i].data);
		ft_printf("type: %i\n", tokens->tokens[i].type);
		i++;
	}
}

void	print_tab(char **tab)
{
	size_t	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		ft_printf("tab %i: %s\n", i, tab[i]);
		i++;
	}
	ft_printf("tab %i: %s\n", i, tab[i]);
}

void	print_lexer(char *line, t_tokens *tokens)
{
	size_t		i;
	const char	*e_type[] = {"WORD", "IO_IN", "IO_OUT",
		"IO_HDOC", "IO_APP", "PIPE", "OR", "AND", "P_START", "P_END"};
	const char	*e_colors[] = {"\x1b[32m", "\x1b[34m", "\x1b[94m",
		"\x1b[35m", "\x1b[95m", "\x1b[33m", "\x1b[93m", "\x1b[93m",
		"\x1b[31m", "\x1b[91m"};

	i = 0;
	ft_printf("\nOrigine:\n%s\n", line);
	ft_printf("Lexer:\n");
	while (i < tokens->size)
	{
		ft_printf("%s", e_colors[tokens->tokens[i].type]);
		ft_printf("%s", e_type[tokens->tokens[i].type]);
		ft_printf("\x1b[0m ");
		i++;
	}
	ft_printf("\n\n");
}

void	show_red(t_redirect **red)
{
	int			i;
	int			type;
	const char	*e_str[] = {"IO_IN", "IO_OUT", "IO_HDOC", "IO_APP"};

	i = -1;
	if (!red)
		return ;
	ft_printf("redirect:");
	if (!red[++i])
		ft_printf("\t(null)\n");
	else
	{
		ft_printf(" file\tfd\ttype\n");
		while (red[i])
		{
			type = red[i]->io_r;
			ft_printf("\t%s\t%i\t%s\n", red[i]->file, red[i]->fd, e_str[type]);
			i++;
		}
	}
}

void	print_node(t_cmd *data)
{
	int		i;

	if (!data)
	{
		ft_printf("\n\t%s\n", data);
		return ;
	}
	ft_printf("\nPath_exec:\t%s\n", data->path_exec);
	i = -1;
	while (data->cmd[++i])
		ft_printf("cmd%i:\t\t%s\n", i, data->cmd[i]);
	show_red(data->redirect);
}
