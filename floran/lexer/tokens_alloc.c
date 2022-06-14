/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_alloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 22:53:12 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/15 00:59:01 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

static t_lxm	*transfer_tokens(t_lxm *from, size_t len, size_t max)
{
	size_t	i;
	t_lxm	*to;

	i = 0;
	to = (t_lxm *)ft_calloc(max, sizeof(t_lxm));
	if (!to)
		return (display_error("Error Allocation\n", 0), NULL);
	while (i < len)
	{
		to[i].data = ft_strdup(from[i].data);
		if (!to[i].data)
			return (display_error("Error Allocation\n", 0), NULL);
		to[i].type = from[i].type;
		i++;
	}
	return (to);
}

static int	tokens_realloc(t_tokens *tokens)
{
	t_lxm	*tmp;

	tmp = transfer_tokens(tokens->tokens, tokens->size, tokens->size);
	if (!tmp)
		return (1);
	tokens->max += BUFFER_LXM;
	free_lxm(tokens->tokens, tokens->size);
	tokens->tokens = transfer_tokens(tmp, tokens->size, tokens->max);
	free_lxm(tmp, tokens->size);
	if (!tokens->tokens)
		return (1);
	return (0);
}

int	tokens_alloc(t_tokens *tokens)
{
	if (tokens->size == 0)
	{
		tokens->max = BUFFER_LXM;
		tokens->tokens = ft_calloc(tokens->max, sizeof(t_lxm));
		if (!tokens->tokens)
			return (1);
	}
	else
	{
		if (tokens_realloc(tokens))
			return (1);
	}
	return (0);
}
