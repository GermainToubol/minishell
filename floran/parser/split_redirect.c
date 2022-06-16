/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 23:11:07 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/16 13:51:17 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "libft.h"
#include "minishell.h"
#include "utils.h"

static size_t	count_red(t_tokens *tokens, size_t start, size_t max)
{
	size_t	i;

	i = 0;
	while (start < max)
	{
		if (tokens->tokens[start].type >= IO_IN
			&& tokens->tokens[start].type <= IO_APP)
			i++;
		start++;
	}
	return (i);
}

static int	get_fd(t_lxm *lxm)
{
	int		i;
	char	*n;

	i = 0;
	n = NULL;
	while (lxm->data[i])
	{
		if (lxm->data[i] == '<' || lxm->data[i] == '>')
			break ;
		i++;
	}
	if (i > 0)
		n = ft_substr(lxm->data, 0, i);
	else if (lxm->data[0] == '<')
		return (0);
	else if (lxm->data[0] == '>')
		return (1);
	if (!n)
		return (display_error("Error allocation\n", 0), -1);
	i = ft_atoi(n);
	free(n);
	return (i);
}

static int	fill_red2(t_tokens *tokens, size_t start,
		size_t *i, t_redirect **red)
{
	int	type;

	red[*i] = ft_calloc(1, sizeof(t_redirect));
	if (!red[*i])
		return (display_error("Error allocation\n", 0), 1);
	type = tokens->tokens[start].type;
	red[*i]->io_r = type - 1;
	red[*i]->fd = get_fd(&tokens->tokens[start++]);
	if (red[*i]->fd == -1)
		return (1);
	red[*i]->file = ft_strdup(tokens->tokens[start].data);
	if (!red[*i]->file)
		return (display_error("Error allocation\n", 0), 1);
	return (0);
}

static int	fill_red(t_tokens *tokens, size_t start,
		size_t max, t_redirect **red)
{
	size_t	i;

	i = 0;
	while (start < max)
	{
		if (tokens->tokens[start].type >= IO_IN
			&& tokens->tokens[start].type <= IO_APP)
		{
			if (fill_red2(tokens, start, &i, red))
				return (1);
			i++;
		}
		start++;
	}
	red[i] = NULL;
	return (0);
}

t_redirect	**fill_redirect(t_tokens *tokens, size_t start,
	size_t max, int *err)
{
	t_redirect	**red;
	size_t		count;

	count = count_red(tokens, start, max);
	red = ft_calloc(count + 1, sizeof(t_redirect *));
	*err = 0;
	if (!red)
	{
		*err = -1;
		return (display_error("Error allocation\n", 0), NULL);
	}
	if (fill_red(tokens, start, max, red))
	{
		*err = -1;
		return (free_red(red), NULL);
	}
	return (red);
}
