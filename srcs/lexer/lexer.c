/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 07:13:55 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/08 16:57:17 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "utils.h"

static int	is_forbidden(char line)
{
	if (ft_isalnum(line) || line == ' ' || line == '\t' || line == '$'
		|| line == '>' || line == '<' || line == '|' || line == '&'
		|| line == '*' || line == '-' || line == '\0' || line == '"'
		|| line == '\'' || line == '(' || line == ')' || line == '.'
		|| line == '/' || line == '_')
		return (1);
	error_syntax(line);
	return (0);
}

static int	is_end(char *line, t_tokens *tokens)
{
	int		is_open;
	size_t	i;

	if (*line == '\0')
	{
		if (tokens->size > 0 && tokens->tokens[tokens->size - 1].type <= IO_APP
			&& tokens->tokens[tokens->size - 1].type >= IO_IN)
			return (error_syntax('\n'), 1);
		if (tokens->size > 0 && tokens->tokens[tokens->size - 1].type <= AND
			&& tokens->tokens[tokens->size - 1].type >= PIPE)
			return (error_syntax_str("minishell: syntax error: "
					"unexpected end of file\n", 0), 1);
		is_open = 0;
		i = -1;
		while (++i < tokens->size)
		{
			if (tokens->tokens[i].type == P_START)
				is_open++;
			if (tokens->tokens[i].type == P_END)
				is_open--;
		}
		if (is_open > 0)
			return (error_syntax('('), 1);
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
	len = is_prio(line, &tokens->tokens[tokens->size], tokens);
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
	if (!line)
		return (1);
	if (tokens_alloc(tokens))
		return (1);
	if (convert_tokens(line, tokens))
	{
		del_hdoc_token(tokens);
		return (free_lxm(tokens->tokens, tokens->size), 1);
	}
	return (0);
}
