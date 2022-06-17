/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 14:49:47 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/17 12:36:59 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "libft.h"
#include "utils.h"

size_t	get_n_sep(t_tokens *tokens)
{
	size_t	r;
	size_t	i;
	int		type;

	i = 0;
	r = 0;
	while (i < tokens->size)
	{
		type = tokens->tokens[i++].type;
		if (type == PIPE || type == OR || type == AND)
			r++;
	}
	if (i > 0 && tokens->tokens[i - 1].type >= PIPE
		&& tokens->tokens[i - 1].type <= AND)
		r = (r * 2);
	else if (i > 0)
		r = 1 + (r * 2);
	i = 0;
	while (i < tokens->size)
	{
		type = tokens->tokens[i++].type;
		if (type == P_START || type == P_END)
			r++;
	}
	return (r);
}

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

int	fill_cmd_line(t_tokens *tokens, t_parse **cmd_line)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	while (i < tokens->size)
	{
		cmd_line[k] = ft_calloc(1, sizeof(t_parse));
		if (!cmd_line[k])
			return (display_error("Error allocation\n", 0), 1);
		if (tokens->tokens[i].type >= PIPE && tokens->tokens[i].type <= P_END)
		{
			cmd_line[k]->cmd = NULL;
			cmd_line[k++]->type = tokens->tokens[i++].type;
		}
		else
		{
			cmd_line[k]->type = CMD;
			cmd_line[k]->cmd = fill_cmd(tokens, &i);
			if (!cmd_line[k++]->cmd)
				return (1);
		}
	}
	cmd_line[k] = NULL;
	return (0);
}

t_parse	**create_cmd_line(t_tokens *tokens)
{
	t_parse	**ret;
	size_t	size;

	size = get_n_sep(tokens);
	ret = ft_calloc(size + 1, sizeof(t_parse *));
	if (!ret)
		return (display_error("Error allocation\n", 0), NULL);
	if (fill_cmd_line(tokens, ret))
		return (free_parse(ret), NULL);
	return (ret);
}

t_parse	**parser(t_tokens *tokens)
{
	t_parse	**cmd_line;

	cmd_line = create_cmd_line(tokens);
	free_lxm(tokens->tokens, tokens->size);
	if (!cmd_line)
		return (NULL);
	print_cmd_line(cmd_line);
	print_cmd_line_detail(cmd_line);
	return (cmd_line);
}
