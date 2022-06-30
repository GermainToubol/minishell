/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_hdoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 13:48:24 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/30 14:49:55 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "lexer.h"
#include "parser.h"
#include "libft.h"
#include "minishell.h"

static int	unlink_hdoc(char *name)
{
	if (unlink(name) == -1)
		return (1);
	return (0);
}

int	del_hdoc_token(t_tokens *tokens)
{
	size_t	i;

	i = 0;
	while (i < tokens->size)
	{
		if (i > 0 && tokens->tokens[i - 1].type == IO_HDOC)
		{
			if (unlink_hdoc(tokens->tokens[i].data))
				return (1);
		}
		i++;
	}
	return (0);
}

int	del_hdoc_parse(t_parse **parse)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (parse[i])
	{
		if (parse[i]->type == CMD && parse[i]->cmd->redirect)
		{
			j = 0;
			while (parse[i]->cmd->redirect[j])
			{
				if (parse[i]->cmd->redirect[j]->io_r == HDOC)
				{
					if (unlink_hdoc(parse[i]->cmd->redirect[j]->file))
						return (1);
				}
				j++;
			}
		}
		i++;
	}
	return (0);
}
