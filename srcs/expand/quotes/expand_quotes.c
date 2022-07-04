/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:46:09 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/04 23:11:45 by fmauguin         ###   ########.fr       */
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
	return (ret);
}
