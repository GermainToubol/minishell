/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 14:49:47 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/03 18:12:44 by fmauguin         ###   ########.fr       */
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

t_parse	**create_cmd_line(t_tokens *tokens)
{
	t_parse	**ret;
	size_t	size;

	size = get_n_sep(tokens);
	ret = ft_calloc(size + 1, sizeof(t_parse *));
	if (!ret)
		return (display_error("Error allocation\n", 0), NULL);
	if (fill_cmd_line(tokens, ret, size))
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
	return (cmd_line);
}
