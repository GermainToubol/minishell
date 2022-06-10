/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 12:36:12 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/10 18:27:44 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "floran.h"

static void	first_cmd2(char *cmd, unsigned int *i, unsigned int *len)
{
	while (*i > 0 && ft_isdigit(cmd[*i - 1]))
		(*i)--;
	while (cmd[*i + *len] && cmd[*i + *len] != '<' && cmd[*i + *len] != '>')
		(*len)++;
	if (cmd[*i + *len] == '\0')
		return ;
	else
	{
		(*len)--;
		while ((*len) > 0 && ft_isdigit(cmd[*i + *len]))
			(*len)--;
		if (*len == 0 || !ft_iswhitspaces(cmd[*i - 1 + *len]))
			while (ft_isdigit(cmd[*i + *len]))
				(*len)++;
	}
}

unsigned int	first_cmd(char *cmd, unsigned int i, unsigned int *len)
{
	*len = 0;
	while (ft_iswhitspaces(cmd[i]))
		i++;
	while (ft_isdigit(cmd[i]))
		i++;
	if (cmd[i] == '<' || cmd[i] == '>')
	{
		i++;
		while (ft_iswhitspaces(cmd[i]))
			i++;
		while (cmd[i] && !ft_iswhitspaces(cmd[i]) && cmd[i] != '<'
			&& cmd[i] != '>')
			i++;
		return (first_cmd(cmd, i, len));
	}
	else
	{
		first_cmd2(cmd, &i, len);
		return (i);
	}
}
