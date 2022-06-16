/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:11:19 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/16 03:26:48 by fmauguin         ###   ########.fr       */
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

void	print_cmd_line(t_parse **parse)
{
	size_t		i;
	const char	*e_type[] = {"CMD", "PIPE", "OR", "AND", "P_START", "P_END"};
	const char	*e_colors[] = {"\x1b[32m", "\x1b[33m", "\x1b[36m", "\x1b[34m",
		"\x1b[35m", "\x1b[31m"};
	int			type;

	i = 0;
	ft_printf("cmd_line:\n");
	while (parse[i])
	{
		type = parse[i]->type;
		if (type == CMD)
			type = 0;
		if (type >= PIPE)
			type -= 4;
		ft_printf("%s", e_colors[type]);
		ft_printf("%s", e_type[type]);
		ft_printf("\x1b[0m ");
		i++;
	}
	ft_printf("\n\n");
}
