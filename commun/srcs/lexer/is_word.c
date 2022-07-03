/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_word.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 17:18:36 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/03 14:56:19 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "utils.h"

static int	is_quote_content(char *line, size_t *i)
{
	int		sq_open;
	int		dq_open;

	dq_open = 0;
	sq_open = 0;
	while (line[*i])
	{
		if (!sq_open && !dq_open && (line[*i] == ' ' || line[*i] == '\t'
				|| line[*i] == '|' || line[*i] == '&' || line[*i] == '>'
				|| line[*i] == '<' || line[*i] == '\0' || line[*i] == '('
				|| line[*i] == ')'))
			break ;
		(*i)++;
		if (line[*i] == '\'' && !dq_open)
			sq_open = !sq_open;
		if (line[*i] == '"' && !sq_open)
			dq_open = !dq_open;
		(*i)++;
	}
	if (sq_open)
		return (display_error(NULL, '\''), 1);
	if (dq_open)
		return (display_error(NULL, '"'), 1);
	return (0);
}

int	is_quote(char *line, t_lxm *lxm, t_tokens *tokens, size_t *i)
{
	*i = 0;
	if (is_quote_content(line, i))
		return (-1);
	lxm->data = ft_strndup(line, *i);
	if (!lxm->data)
		return (display_error("Error allocation\n", 0), -1);
	lxm->type = WORD;
	tokens->size++;
	return (*i);
}

static int	is_word_basic(char *line, t_lxm *lxm, t_tokens *tokens, size_t *i)
{
	if (!ft_isalnum(*line) && *line != '-' && *line != '"' && *line != '\''
		&& *line != '*' && *line != '/' && *line != '.')
		return (0);
	while (!(line[*i] == ' ' || line[*i] == '\t'
		|| line[*i] == '|' || line[*i] == '&' || line[*i] == '>'
		|| line[*i] == '<' || line[*i] == '\0' || line[*i] == '('
		|| line[*i] == ')'))
		(*i)++;
	{
		lxm->data = ft_strndup(line, *i);
		if (!lxm->data)
			return (display_error("Error allocation\n", 0), -1);
		lxm->type = WORD;
		tokens->size++;
	}
	return (0);
}

static int	is_var(char *line, t_lxm *lxm, t_tokens *tokens, size_t *i)
{
	(*i)++;
	while (!(line[*i] == ' ' || line[*i] == '\t'
		|| line[*i] == '|' || line[*i] == '&' || line[*i] == '>'
		|| line[*i] == '<' || line[*i] == '\0' || line[*i] == '('
		|| line[*i] == ')'))
		(*i)++;
	if (line[*i] == '"' || line[*i] == '\'')
	{
		if (is_quote_content(line, i))
			return (1);
	}
	lxm->data = ft_strndup(line, *i);
	if (!lxm->data)
		return (display_error("Error allocation\n", 0), 1);
	lxm->type = WORD;
	tokens->size++;
	return (0);
}

int	is_word(char *line, t_lxm *lxm, t_tokens *tokens)
{
	size_t	i;
	size_t	is_word;

	i = 0;
	is_word = tokens->size;
	if (is_word_basic(line, lxm, tokens, &i) == -1)
		return (-1);
	if (i > 0 && (line[i] == '>' || line[i] == '<')
		&& word_redirect(line, lxm, tokens, &i))
		return (-1);
	if (*line == '$' && is_var(line, lxm, tokens, &i))
		return (-1);
	else if (line[i] == '"' || line[i] == '\'')
	{
		if (is_quote(line, lxm, tokens, &i) == -1)
			return (-1);
	}
	if (is_word != tokens->size && tokens->size > 1
		&& tokens->tokens[tokens->size - 2].type == IO_HDOC
		&& lxm->type == WORD && set_hdoc(&lxm->data))
		return (-1);
	return (i);
}
