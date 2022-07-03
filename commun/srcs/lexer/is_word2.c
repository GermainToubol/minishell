/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_word2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 17:18:36 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/03 12:50:03 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "utils.h"

int	word_redirect(char *line, t_lxm *lxm, t_tokens *tokens, size_t *i)
{
	long long	n;

	(*i)--;
	while (*i > 0 && ft_isdigit(line[*i]))
		(*i)--;
	if (ft_isdigit(line[*i]) && *i == 0)
	{
		n = ft_atoll(line);
		if (n <= 2147483647 && n >= 0)
			return (0);
	}
	while (ft_isalnum(line[*i]) || ((line[*i] == '-' || line[*i] == '*'
				|| line[*i] == '/' || line[*i] == '.' || line[*i] == '=')))
		(*i)++;
	lxm->data = ft_strndup(line, *i);
	if (!lxm->data)
		return (display_error("Error allocation\n", 0), 1);
	lxm->type = WORD;
	tokens->size++;
	return (0);
}
