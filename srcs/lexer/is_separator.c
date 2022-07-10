/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_separator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 16:51:57 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/08 17:08:19 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

static int	is_pipe(char *line, t_lxm *lxm, t_tokens *tokens, int *i)
{
	if (line[1] == '|')
	{
		lxm->data = ft_strndup("||", 2);
		if (!lxm->data)
			return (error_alloc(), 1);
		lxm->type = OR;
		*i = 2;
	}
	else
	{
		lxm->data = ft_strndup("|", 1);
		if (!lxm->data)
			return (error_alloc(), 1);
		lxm->type = PIPE;
		*i = 1;
	}
	tokens->size++;
	return (0);
}

static int	is_ampersand(char *line, t_lxm *lxm, t_tokens *tokens, int *i)
{
	if (line[1] == '&')
	{
		lxm->data = ft_strndup("&&", 2);
		if (!lxm->data)
			return (error_alloc(), 1);
		lxm->type = AND;
		tokens->size++;
		*i = 2;
	}
	else
		return (error_syntax(*line), 1);
	return (0);
}

int	is_separator(char *line, t_lxm *lxm, t_tokens *tokens)
{
	int	i;

	i = 0;
	if (!(*line == '|' || *line == '&'))
		return (i);
	if (tokens->size == 0 || (tokens->size > 0
			&& tokens->tokens[tokens->size - 1].type >= IO_IN
			&& tokens->tokens[tokens->size - 1].type <= P_START))
	{
		if (line[1] == '|' || line[1] == '&')
			return (error_syntax_str(line, 2), -1);
		return (error_syntax(*line), -1);
	}
	if (*line == '|')
	{
		if (is_pipe(line, lxm, tokens, &i))
			return (-1);
	}
	else if (*line == '&')
	{
		if (is_ampersand(line, lxm, tokens, &i))
			return (-1);
	}
	return (i);
}
