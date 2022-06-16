/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 00:58:06 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/16 16:22:03 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "libft.h"
#include "utils.h"

int	main(int ac, char **av, char **envp)
{
	char		*line;
	t_tokens	tokens;

	if (ac > 2)
		return (display_error("Error\nusage: ./minishell\n", 0), 1);
	ft_printf("\x1b[32mWelcome to lexer\n\x1b[0m");
	(void)av;
	while (1)
	{
		line = readline("\x1b[33mMINISHELL$> \x1b[0m");
		if (!line)
			return (1);
		if (lexer(line, &tokens))
			return (free(line), 1);
		print_lexer(line, &tokens);
		free(line);
		if (parser(&tokens, envp))
			return (1);
	}
	return (0);
}
