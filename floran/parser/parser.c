/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 14:49:47 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/15 16:24:36 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "libft.h"

int	parser(t_tokens *tokens, char **env)
{
	char	**path;

	path = get_path(env);
	if (!path)
		return (1);
	(void)tokens;
	return (0);
}
