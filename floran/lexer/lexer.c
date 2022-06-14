/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 07:13:55 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/14 19:47:50 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

int	is_forbidden(char line)
{
	if (ft_isalnum(line) || line == ' ' || line == '\t' || line == '\n'
		|| line == '$' || line == '>' || line == '<' || line == '|'
		|| line == '?' || line == '&' || line == '*' || line == '-'
		|| line == '\0' || line == '"' || line == '\'')
		return (1);
	display_error(NULL, line);
	return (0);
}

static int	is_end(char *line, t_tokens *tokens)
{
	if (*line == '\0')
	{
		if (tokens->size > 0 && tokens->tokens[tokens->size - 1].type <= IO_APP
			&& tokens->tokens[tokens->size - 1].type >= IO_IN)
			return (display_error(NULL, '\n'), 1);
	}
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
			return (1);
		line += len;
		if (*line == ' ' || *line == '\t')
			line++;
		if (is_end(line, tokens))
			return (1);
	}
	return (0);
}

int	main(void)
{
	char		*line;
	t_tokens	tokens;

	while (1)
	{
		line = readline("MINISHELL$> ");
		if (!line)
			return (1);
		if (convert_tokens(line, &tokens))
			return (free(line), 1);
		free(line);
	}
	return (0);
}
