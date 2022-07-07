/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 02:04:44 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/07 22:12:46 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include "g_minishell.h"

int	get_var(const char *cmd, size_t *i, char **ret)
{
	char	*var;
	size_t	start;

	start = *i;
	if (ft_isdigit(cmd[*i]) && (*i)++)
		return (*ret = NULL, 0);
	if (cmd[*i] == '?' && (*i)++)
		return (*ret = get_status_str(), 0);
	while (ft_isalnum(cmd[*i]) || cmd[*i] == '_')
		(*i)++;
	var = ft_substr(cmd, start, *i - start);
	if (!var)
		return (error_alloc(), 1);
	*ret = environment_get(environment_call(), var);
	free(var);
	if (!*ret)
		return (0);
	*ret = ft_strdup(*ret);
	if (!ret)
		return (error_alloc(), 1);
	return (0);
}
