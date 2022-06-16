/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 00:55:31 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/16 01:49:35 by fmauguin         ###   ########.fr       */
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
			&& (start == 0 || tokens->tokens[start - 1].type == WORD))
		{
			while(tokens->tokens[start++].type == WORD)
				i++;
		}
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
			&& (start == 0 || tokens->tokens[start - 1].type == WORD
			|| tokens->tokens[start - 1].type == P_START))
		{
			while(tokens->tokens[start].type == WORD)
			{
				cmdn[i] = ft_strdup(tokens->tokens[start++].data);
				if (!cmdn[i++])
					return (display_error("Error allocation\n", 0), 1);
			}
		}
		start++;
	}
	cmdn[i] = NULL;
	return (0);
}

char	**fill_cmdn(t_tokens *tokens, size_t start, size_t max)
{
	char	**cmdn;
	size_t	count;

	count = count_arg(tokens, start, max);
	cmdn = ft_calloc(count + 1, sizeof(char *));
	if (!cmdn)
		return (display_error("Error allocation\n", 0), NULL);
	if (fill_cmdn2(tokens, start, max, cmdn))
		return (free_tab(cmdn), NULL);
	return (cmdn);
}