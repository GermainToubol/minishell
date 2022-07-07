/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_word.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 17:18:36 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/07 14:06:16 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "utils.h"
#include "g_minishell.h"

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

static int	is_quote(char *line, t_lxm *lxm, t_tokens *tokens, size_t *i)
{
	*i = 0;
	if (is_quote_content(line, i))
		return (1);
	lxm->data = ft_strndup(line, *i);
	if (!lxm->data)
		return (display_error("Error allocation\n", 0), 1);
	lxm->type = WORD;
	tokens->size++;
	return (0);
}

static int	word_redirect(char *line, t_lxm *lxm, t_tokens *tokens, size_t *i)
{
	long long	n;

	(*i)--;
	while (*i > 0 && ft_isdigit(line[*i]))
		(*i)--;
	if (ft_isdigit(line[*i]) && *i == 0)
	{
		if (!ft_atoll(line, &n) && n <= 2147483647 && n >= 0)
			return (0);
	}
	while (!c_separator(line[*i]))
		(*i)++;
	if ((line[*i] == '"' || line[*i] == '\'') && is_quote_content(line, i))
		return (1);
	lxm->data = ft_strndup(line, *i);
	if (!lxm->data)
		return (display_error("Error allocation\n", 0), 1);
	lxm->type = WORD;
	tokens->size++;
	return (0);
}

static int	is_word_basic(char *line, t_lxm *lxm, t_tokens *tokens, size_t *i)
{
	if (c_separator(line[*i]))
		return (0);
	while (!c_separator(line[*i]))
		(*i)++;
	if ((line[*i] == '"' || line[*i] == '\'') && is_quote_content(line, i))
		return (1);
	if (line[*i] == '>' || line[*i] == '<' )
		return (0);
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
	if (is_word_basic(line, lxm, tokens, &i))
		return (-1);
	if (i > 0 && (line[i] == '>' || line[i] == '<')
		&& word_redirect(line, lxm, tokens, &i))
		return (-1);
	else if ((line[i] == '"' || line[i] == '\'')
		&& is_quote(line, lxm, tokens, &i))
		return (-1);
	if (is_interupted() || (is_word != tokens->size && tokens->size > 1
		&& tokens->tokens[tokens->size - 2].type == IO_HDOC
							&& lxm->type == WORD && set_hdoc(&lxm->data)))
		return (-1);
	return (i);
}
