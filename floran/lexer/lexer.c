/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 07:13:55 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/15 00:58:23 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

static int	is_forbidden(char line)
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

static int	convert_tokens_content(char *line, t_tokens *tokens)
{
	int	len;

	len = is_word(line, &tokens->tokens[tokens->size], tokens);
	if (len == -1)
		return (-1);
	else if (len > 0)
		return (len);
	len = is_redirect(line, &tokens->tokens[tokens->size], tokens);
	if (len == -1)
		return (-1);
	else if (len > 0)
		return (len);
	len = is_separator(line, &tokens->tokens[tokens->size], tokens);
	if (len == -1)
		return (-1);
	else if (len > 0)
		return (len);
	return (0);
}

int	convert_tokens(char *line, t_tokens *tokens)
{
	int	len;

	while (*line)
	{
		if (!is_forbidden(*line))
			return (1);
		if (tokens->size == tokens->max)
		{
			if (tokens_alloc(tokens))
				return (1);
		}
		len = convert_tokens_content(line, tokens);
		if (len == -1)
			return (1);
		else
			line += len;
		if (*line == ' ' || *line == '\t')
			line++;
		if (is_end(line, tokens))
			return (1);
	}
	return (0);
}

int	lexer(char *line, t_tokens *tokens)
{
	tokens->size = 0;
	if (tokens_alloc(tokens))
		return (1);
	if (convert_tokens(line, tokens))
		return (1);
	return (0);
}
