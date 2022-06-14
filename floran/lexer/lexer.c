/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 07:13:55 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/14 18:18:24 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

int	is_forbidden(char line)
{
	if (ft_isalnum(line) || line == ' ' || line == '\t' || line == '\n'
		|| line == '$' || line == '>' || line == '<' || line == '|'
		|| line == '?' || line == '&' || line == '*' || line == '-'
		|| line == '\0')
		return (1);
	display_error(NULL, line);
	return (0);
}

int	convert_tokens(char *line, t_tokens *tokens)
{
	int	len;

	tokens->size = 0;
	while (*line)
	{
		if (!is_forbidden(*line))
			return (1);
		len = is_word(line, &tokens->tokens[tokens->size], tokens);
		if (len == -1)
			return (1);
		line += len;
		len = is_redirect(line, &tokens->tokens[tokens->size], tokens);
		if (len == -1)
			return (1);
		line += len;
		len = is_separator(line, &tokens->tokens[tokens->size], tokens);
		if (len == -1)
			return (print_tokens(tokens), 1);
		line += len;
		if (*line == ' ' || *line == '\t')
			line++;
	}
	print_tokens(tokens);
	return (0);
}

int	main(void)
{
	char		*line;
	t_tokens	tokens;

	line = readline("MINISHELL$> ");
	if (!line)
		return (1);
	if (convert_tokens(line, &tokens))
		return (free(line), 1);
	free(line);
	return (0);
}
