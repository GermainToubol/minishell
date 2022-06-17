/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 00:58:06 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/17 12:36:07 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "libft.h"
#include "utils.h"

int	main(int ac, char **av)
{
	char		*line;
	t_tokens	tokens;
	t_parse		**parse;

	if (ac > 2)
		return (display_error("Error\nusage: ./minishell\n", 0), 1);
	ft_printf("\x1b[32mWelcome to lexer\n\x1b[0m");
	(void)av;
	while (1)
	{
		line = readline("MINISHELL$> ");
		if (lexer(line, &tokens))
			return (free(line), 1);
		print_lexer(line, &tokens);
		free(line);
		parse = parser(&tokens);
		if (!parse)
			return (1);
	free_parse(parse);
	}
	return (0);
}
