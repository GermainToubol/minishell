/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_word.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 17:18:36 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/15 13:14:35 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

static int	is_quote_content(char *line, int sq_open, int dq_open, size_t *i)
{
	while (line[*i])
	{
		if (!sq_open && !dq_open && (line[*i] == ' ' || line[*i] == '\t'
				|| line[*i] == '|' || line[*i] == '&' || line[*i] == '>'
				|| line[*i] == '<' || line[*i] == '\0'))
			break ;
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
	int		sq_open;
	int		dq_open;

	*i = 0;
	dq_open = 0;
	sq_open = 0;
	if (is_quote_content(line, sq_open, dq_open, i))
		return (-1);
	lxm->data = ft_strndup(line, *i);
	if (!lxm->data)
		return (display_error("Error allocation\n", 0), -1);
	lxm->type = WORD;
	tokens->size++;
	return (*i);
}

static int	word_redirect(char *line, t_lxm *lxm, t_tokens *tokens, size_t *i)
{
	long long	n;

	(*i)--;
	while (*i > 0 && ft_isdigit(line[*i]))
		(*i)--;
	if (ft_isdigit(line[*i]) && *i == 0)
	{
		n = ft_atoll(line);
		if (n <= 2147483647 && n >= 0)
			return (0);
	}
	while (ft_isalnum(line[*i]))
		(*i)++;
	lxm->data = ft_strndup(line, *i);
	if (!lxm->data)
		return (display_error("Error allocation\n", 0), 1);
	lxm->type = WORD;
	tokens->size++;
	return (0);
}

static int	is_word_basic(char *line, t_lxm *lxm, t_tokens *tokens, size_t *i)
{
	if (!ft_isalnum(*line) && *line != '-' && *line != '"'
		&& *line != '\'' && *line != '$')
		return (0);
	if (*line == '$')
		(*i)++;
	while (ft_isalnum(line[*i]) || (line[*i] == '-' && *line != '$'))
		(*i)++;
	if ((line[*i] == '\0' || line[*i] == ' ' || line[*i] == '\t'
			|| line[*i] == '|' || line[*i] == '&' || line[*i] == '('
			|| line[*i] == ')') || line[0] == '$')
	{
		if (*line == '$' && line[1] == '?')
			(*i) = 2;
		lxm->data = ft_strndup(line, *i);
		if (!lxm->data)
			return (display_error("Error allocation\n", 0), -1);
		lxm->type = WORD;
		tokens->size++;
	}
	return (0);
}

int	is_word(char *line, t_lxm *lxm, t_tokens *tokens)
{
	size_t	i;

	i = 0;
	if (is_word_basic(line, lxm, tokens, &i) == -1)
		return (-1);
	if (i > 0 && (line[i] == '>' || line[i] == '<'))
	{
		if (word_redirect(line, lxm, tokens, &i))
			return (-1);
	}
	else if (line[i] == '"' || line[i] == '\'')
	{
		if (is_quote(line, lxm, tokens, &i) == -1)
			return (-1);
	}
	return (i);
}
