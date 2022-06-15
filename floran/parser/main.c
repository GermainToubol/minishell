/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 00:58:06 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/15 01:01:28 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

int	main(void)
{
	char		*line;
	t_tokens	tokens;

	ft_printf("\x1b[32mWelcome to lexer\n\x1b[0m");
	while (1)
	{
		line = readline("\x1b[33mMINISHELL$> \x1b[0m");
		if (!line)
			return (1);
		if (lexer(line, &tokens))
			return (free(line), 1);
		print_lexer(line, &tokens);
		free(line);
		free_lxm(tokens.tokens, tokens.size);
	}
	return (0);
}
