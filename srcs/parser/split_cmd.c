/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 00:55:31 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/07 22:12:46 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "libft.h"
#include "minishell.h"
#include "utils.h"

static size_t	count_arg(t_tokens *tokens, size_t start, size_t max)
{
	size_t	i;

	i = 0;
	while (start < max)
	{
		if (tokens->tokens[start].type == WORD
			&& (start == 0 || (tokens->tokens[start - 1].type < IO_IN
					|| tokens->tokens[start - 1].type > IO_APP)))
				i++;
		start++;
	}
	return (i);
}

static int	fill_cmdn2(t_tokens *tokens, size_t start,
		size_t max, char **cmdn)
{
	size_t	i;

	i = 0;
	while (start < max)
	{
		if (tokens->tokens[start].type == WORD
			&& (start == 0 || (tokens->tokens[start - 1].type < IO_IN
					|| tokens->tokens[start - 1].type > IO_APP)))
		{
			cmdn[i] = ft_strdup(tokens->tokens[start].data);
			if (!cmdn[i++])
				return (error_alloc(), 1);
		}
		start++;
	}
	cmdn[i] = NULL;
	return (0);
}

char	**fill_cmdn(t_tokens *tokens, size_t start, size_t max, int *err)
{
	char	**cmdn;
	size_t	count;

	count = count_arg(tokens, start, max);
	*err = 0;
	cmdn = ft_calloc(count + 1, sizeof(char *));
	if (!cmdn)
	{
		*err = -1;
		return (error_alloc(), NULL);
	}
	if (fill_cmdn2(tokens, start, max, cmdn))
	{
		*err = -1;
		return (free_tab(cmdn), NULL);
	}
	return (cmdn);
}
