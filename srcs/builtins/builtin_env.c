/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 18:24:59 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/17 18:33:32 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "libft.h"
#include "minishell.h"
#include "g_minishell.h"

int	builtin_env(int argc, char **argv, t_list **env)
{
	t_dico	*dico;
	t_list	*tmp;
	int		status;

	(void)argc;
	(void)argv;
	tmp = *env;
	status = 0;
	while (tmp != NULL)
	{
		dico = (t_dico *)tmp->content;
		if (dico->value != NULL)
		{
			if (ft_printf("%s=%s\n", dico->key, dico->value) < 0)
				status = 125;
		}
		tmp = tmp->next;
	}
	if (status != 0)
		perror("env: write error");
	return (status);
}
