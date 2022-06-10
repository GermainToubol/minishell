/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 09:00:40 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/10 10:38:52 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "floran.h"

static int	has_word(char *str)
{
	if (*str == '>')
		str++;
	while (ft_iswhitspaces(*str))
		str++;
	if (!*str)
		return (error_msg("syntax error near unexpected \
token `newline'", NO_EXIT, 2), 0);
	if (*str == '<')
		return (error_msg("syntax error near unexpected \
token `<'", NO_EXIT, 2), 0);
	if (*str == '>')
		return (error_msg("syntax error near unexpected \
token `>'", NO_EXIT, 2), 0);
	if (*str == '|')
		return (error_msg("syntax error near unexpected \
token `|'", NO_EXIT, 2), 0);
	if (*str == '&')
		return (error_msg("syntax error near unexpected \
token `&'", NO_EXIT, 2), 0);
	return (1);
}

static int	check_pipe(char *str)
{
	if (*str == '|' && *(str + 1) == '|')
		str++;
	else if (*str == '&' && *(str + 1) == '&')
		str++;
	else if (*str == '|' && *(str + 1) == '&')
		return (error_msg("not to handle \
token `&'", NO_EXIT, 2), 0);
	else if (*str == '&' && *(str + 1) != '&')
		return (error_msg("not to handle \
token `&'", NO_EXIT, 2), 0);
	str++;
	while (*str && ft_iswhitspaces(*str))
		str++;
	if (*str == '|')
		return (error_msg("syntax error near unexpected \
token `|'", NO_EXIT, 2), 0);
	if (*str == '&')
		return (error_msg("syntax error near unexpected \
token `&'", NO_EXIT, 2), 0);
}

int	check_line(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '<')
		{
			if (str[i + 1] == '<')
			{
				i++;
				if (!has_word(&str[++i]))
					return (0);
			}
			else
				if (!has_word(&str[++i]))
					return (0);
		}
		if (str[i] == '>')
			if (!has_word(&str[++i]))
				return (0);
		if (str[i] == '|' || str[i] == '&')
			if (!check_pipe(&str[i]))
				return (0);
	}
	return (1);
}
