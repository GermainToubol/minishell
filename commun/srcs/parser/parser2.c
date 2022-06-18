/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 16:36:58 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/18 16:39:18 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "libft.h"
#include "utils.h"

static t_cmd	*fill_cmd(t_tokens *tokens, size_t *start)
{
	t_cmd	*cmd;
	size_t	max;
	int		err;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	max = *start;
	while (max < tokens->size && tokens->tokens[max].type < PIPE)
		max++;
	cmd->redirect = fill_redirect(tokens, *start, max, &err);
	cmd->cmd = fill_cmdn(tokens, *start, max, &err);
	if (err == -1)
		return (free_cmd(cmd), NULL);
	cmd->path_exec = NULL;
	*start = max;
	return (cmd);
}

static t_parse	*create_parse(t_tokens *tokens, size_t *i)
{
	t_parse	*new;

	new = ft_calloc(1, sizeof(t_parse));
	if (!new)
		return (display_error("Error allocation\n", 0), NULL);
	if (tokens->tokens[*i].type >= PIPE && tokens->tokens[*i].type <= P_END)
	{
		new->cmd = NULL;
		new->type = tokens->tokens[(*i)++].type;
	}
	else
	{
		new->type = CMD;
		new->cmd = fill_cmd(tokens, i);
		if (!new->cmd)
			return (NULL);
	}
	return (new);
}

int	fill_cmd_line(t_tokens *tokens, t_parse **cmd_line, size_t size)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	while (i < tokens->size)
	{
		cmd_line[k] = create_parse(tokens, &i);
		if (!cmd_line[k++])
			return (1);
	}
	if (k < size)
	{
		cmd_line[k] = ft_calloc(1, sizeof(t_parse));
		if (!cmd_line[k])
			return (display_error("Error allocation\n", 0), 1);
		cmd_line[k]->type = CMD;
		cmd_line[k++]->cmd = NULL;
	}
	cmd_line[k] = NULL;
	return (0);
}
