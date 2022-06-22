/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:03:47 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/22 15:09:38 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "minishell.h"
#include "g_minishell.h"

int	is_builtin(char *name)
{
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
