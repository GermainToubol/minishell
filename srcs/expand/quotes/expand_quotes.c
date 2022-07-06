/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:46:09 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/07 00:36:00 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "libft.h"
#include "utils.h"

char	*quotes(const char *cmd)
{
	char	*ret;
	char	*tmp;

	ret = NULL;
	tmp = ft_substr(cmd, 1, skip_quote(cmd) - 2);
	if (cmd[0] == '\'' && strjoin_custom(&ret, tmp))
		return (NULL);
	else if (cmd[0] == '"')
	{
		if (strjoin_custom(&ret, expand_var_quotes(tmp)))
			return (NULL);
	}
	ft_printf("ret %s\n", ret);
	if (add_backslash(&ret))
		return (free(ret), NULL);
	ft_printf("ret %s\n", ret);
	return (ret);
}
