/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_word.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 17:18:36 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/14 18:19:02 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

static int	word_redirect(char *line, t_lxm *lxm, t_tokens *tokens, size_t *i)
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
	while (ft_isalnum(line[*i]))
		(*i)++;
	lxm->data = ft_strndup(line, *i);
	if (!lxm->data)
		return (display_error("Error allocation\n", 0), 1);
	lxm->type = WORD;
	tokens->size++;
	return (0);
}

int	is_word(char *line, t_lxm *lxm, t_tokens *tokens)
{
	size_t	i;

	if (!ft_isalnum(*line) && *line != '-')
		return (0);
	i = 0;
	while (ft_isalnum(line[i]) || line[i] == '-')
		i++;
	if (line[i] == '\0' || line[i] == ' ' || line[i] == '\t' || line[i] == '|'
		|| line[i] == '&')
	{
		lxm->data = ft_strndup(line, i);
		if (!lxm->data)
			return (display_error("Error allocation\n", 0), -1);
		lxm->type = WORD;
		tokens->size++;
	}
	else if (line[i] == '>' || line[i] == '<')
		if (word_redirect(line, lxm, tokens, &i))
			return (-1);
	return (i);
}
