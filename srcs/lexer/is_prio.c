/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_prio.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 12:04:22 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/08 15:44:55 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "utils.h"

static int	check_next_token(char *line)
{
	size_t	i;

	i = 0;
	while (*line == ' ' || *line == '\t' || *line == '\n')
		line++;
	if (*line == '|' || *line == '&' || *line == '\0' || *line == '('
		|| *line == ')')
		return (0);
	else
	{
		while (line[i] && line[i] != ' ' && line[i] != '\t'
			&& line[i] != '\n')
			i++;
		return (error_syntax_str(line, i + 1), 1);
	}
}

static int	is_p_end(char *line, t_lxm *lxm, t_tokens *tokens, int is_open)
{
	size_t	i;

	if (is_open <= 0)
		return (error_syntax(*line), 1);
	if (tokens->size > 0 && tokens->tokens[tokens->size - 1].type == P_END)
	{
		i = 2;
		while (i < tokens->size
			&& tokens->tokens[tokens->size - i].type != P_START)
			i++;
		if (i < tokens->size && tokens->tokens[tokens->size - i].type == P_START
			&& tokens->tokens[tokens->size - i - 1].type == P_START)
			return (error_syntax_str("(())", 5), 1);
	}
	else if (tokens->size > 0 && tokens->tokens[tokens->size - 1].type != WORD)
		return (error_syntax(*line), 1);
	lxm->data = ft_strndup(")", 1);
	if (!lxm->data)
		return (error_alloc(), 1);
	lxm->type = P_END;
	tokens->size++;
	if (check_next_token(&line[1]))
		return (1);
	return (0);
}

static int	is_prio_content(char *line, t_lxm *lxm,
	t_tokens *tokens, int is_open)
{
	if (*line == ')')
	{
		if (is_p_end(line, lxm, tokens, is_open))
			return (1);
	}
	else
	{
		if (tokens->size > 0 && (tokens->tokens[tokens->size - 1].type == P_END
				|| (tokens->tokens[tokens->size - 1].type >= WORD
					&& tokens->tokens[tokens->size - 1].type <= IO_APP)))
			return (error_syntax(*line), 1);
		lxm->data = ft_strndup("(", 1);
		if (!lxm->data)
			return (error_alloc(), 1);
		lxm->type = P_START;
		tokens->size++;
	}
	return (0);
}

int	is_prio(char *line, t_lxm *lxm, t_tokens *tokens)
{
	int		is_open;
	size_t	i;

	if (*line != '(' && *line != ')')
		return (0);
	i = 0;
	is_open = 0;
	while (i < tokens->size)
	{
		if (tokens->tokens[i].type == P_START)
			is_open++;
		if (tokens->tokens[i].type == P_END)
			is_open--;
		i++;
	}
	if (is_prio_content(line, lxm, tokens, is_open))
		return (-1);
	return (1);
}
