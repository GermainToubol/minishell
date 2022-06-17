/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_separator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 16:51:57 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/15 21:49:42 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

static int	is_pipe(char *line, t_lxm *lxm, t_tokens *tokens, int *i)
{
	if (tokens->size > 0 && tokens->tokens[tokens->size - 1].type == P_START
		&& line[1] == '|')
		return (display_error_red(line, 2), -1);
	if (tokens->size > 0 && tokens->tokens[tokens->size - 1].type != WORD
		&& tokens->tokens[tokens->size - 1].type != P_END)
		return (display_error(NULL, *line), -1);
	if (line[1] == '|')
	{
		lxm->data = ft_strndup("||", 2);
		if (!lxm->data)
			return (display_error("Error allocation\n", 0), 1);
		lxm->type = OR;
		*i = 2;
	}
	else
	{
		lxm->data = ft_strndup("|", 1);
		if (!lxm->data)
			return (display_error("Error allocation\n", 0), 1);
		lxm->type = PIPE;
		*i = 1;
	}
	tokens->size++;
	return (0);
}

static int	is_ampersand(char *line, t_lxm *lxm, t_tokens *tokens, int *i)
{
	if (tokens->size > 0 && tokens->tokens[tokens->size - 1].type == P_START
		&& line[1] == '&')
		return (display_error_red(line, 2), -1);
	if (tokens->size > 0 && tokens->tokens[tokens->size - 1].type != WORD
		&& tokens->tokens[tokens->size - 1].type != P_END)
		return (display_error(NULL, *line), -1);
	if (line[1] == '&')
	{
		lxm->data = ft_strndup("&&", 2);
		if (!lxm->data)
			return (display_error("Error allocation\n", 0), 1);
		lxm->type = AND;
		tokens->size++;
		*i = 2;
	}
	else
		return (display_error(NULL, *line), 1);
	return (0);
}

int	is_separator(char *line, t_lxm *lxm, t_tokens *tokens)
{
	int	i;

	i = 0;
	if (*line == '|')
	{
		if (tokens->size == 0)
			return (display_error(NULL, *line), -1);
		if (is_pipe(line, lxm, tokens, &i))
			return (-1);
	}
	else if (*line == '&')
	{
		if (tokens->size == 0)
			return (display_error(NULL, *line), -1);
		if (is_ampersand(line, lxm, tokens, &i))
			return (-1);
	}
	return (i);
}
