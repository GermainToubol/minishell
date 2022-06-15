/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_prio.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 12:04:22 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/15 12:47:21 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

static int	is_prio_content(char *line, t_lxm *lxm,
	t_tokens *tokens, int is_open)
{
	if (*line == ')')
	{
		if (is_open <= 0)
			return (display_error(NULL, *line), 1);
		if (tokens->size > 0 && tokens->tokens[tokens->size].type == P_START)
			return (display_error(NULL, *line), 1);
		lxm->data = ft_strndup(")", 1);
		if (!lxm->data)
			return (display_error("Error allocation\n", 0), 1);
		lxm->type = P_END;
		tokens->size++;
	}
	else
	{
		lxm->data = ft_strndup("(", 1);
		if (!lxm->data)
			return (display_error("Error allocation\n", 0), 1);
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
