/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:03:47 by gtoubol           #+#    #+#             */
/*   Updated: 2022/07/07 12:55:14 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "minishell.h"
#include "g_minishell.h"

int	is_builtin(t_parse *parse)
{
	char	*name;
	size_t	i;

	if (parse->type != CMD || parse->cmd == NULL || parse->cmd->cmd == NULL
		|| parse->cmd->cmd[0] == NULL)
		return (0);
	i = 0;
	while (parse->cmd->cmd[i] != NULL && parse->cmd->cmd[i][0] == '\0')
		i++;
	if (parse->cmd->cmd[i] == NULL)
		ft_tab_shift(parse->cmd->cmd, i - 1);
	else
		ft_tab_shift(parse->cmd->cmd, i);
	name = parse->cmd->cmd[0];
	if (ft_strcmp(name, "echo") == 0
		|| ft_strcmp(name, "cd") == 0
		|| ft_strcmp(name, "pwd") == 0
		|| ft_strcmp(name, "export") == 0
		|| ft_strcmp(name, "unset") == 0
		|| ft_strcmp(name, "env") == 0
		|| ft_strcmp(name, "exit") == 0)
		return (1);
	return (0);
}
