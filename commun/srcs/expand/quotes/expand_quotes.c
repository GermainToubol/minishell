/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:46:09 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/26 17:06:46 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "libft.h"
#include "utils.h"

char	*expand_quotes(char *cmd)
{
	char	*ret;

	ret = NULL;
	if (cmd[0] == '\'')
	{
		ret = ft_substr(cmd, 1, ft_strlen(cmd) - 1);
		if (!ret)
			return (display_error("Error allocation\n", 0), NULL);
	}
	else if (cmd[0] == '"')
	{
		ret = expand_var(&cmd[1]);
		if (!ret)
			return (NULL);
		ret[ft_strlen(ret) - 1] = '\0';
	}
	return (ret);
}