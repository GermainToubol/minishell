/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 09:00:40 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/10 17:28:53 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "floran.h"

static int	forbidden_c(char c)
{
	char	*forbidden;

	forbidden = "!\\;";
	while (*forbidden)
	{
		if (c == *forbidden)
			return (1);
		forbidden++;
	}
	return (0);
}

static int	has_word(char *str)
{
	int	i;

	i = 0;
	if (*str == '>')
		str++;
	while (ft_iswhitspaces(str[i]))
		i++;
	if (i == 0)
	{
		while (ft_isalnum(str[i]))
			i++;
		if (str[i] == '<' || str[i] == '>')
			return (error_msg(ft_substr(str, 0, i), NO_EXIT, 2), 0);
	}
	if (!*str)
		return (error_msg(ft_strdup("newline"), NO_EXIT, 2), 0);
	if (*str == '<' || *str == '>' || *str == '|' || *str == '&')
		return (error_msg(ft_substr(str, 0, 1), NO_EXIT, 2), 0);
	return (1);
}

static int	check_pipe(char *str)
{
	if (*str == '|' && *(str + 1) == '|')
		str++;
	else if (*str == '&' && *(str + 1) == '&')
		str++;
	else if (*str == '|' && *(str + 1) == '&')
		return (error_msg2(ft_strdup("&"), NO_EXIT, 2), 0);
	else if (*str == '&' && *(str + 1) != '&')
		return (error_msg2(ft_strdup("&"), NO_EXIT, 2), 0);
	str++;
	while (*str && ft_iswhitspaces(*str))
		str++;
	if (*str == '|' || *str == '&')
		return (error_msg(ft_substr(str, 0, 1), NO_EXIT, 2), 0);
	return (1);
}

static int	check_line2(char *str, int *i)
{
	if (str[*i] == '<')
	{
		if (str[*i + 1] == '<')
		{
			(*i)++;
			if (!has_word(&str[++(*i)]))
				return (0);
		}
		else
			if (!has_word(&str[++(*i)]))
				return (0);
	}
	if (str[*i] == '>')
		if (!has_word(&str[++(*i)]))
			return (0);
	return (1);
}

int	check_line(char *str)
{
	int	i;

	i = 0;
	while (ft_iswhitspaces(str[i]))
		i++;
	if (str[i] == '\0')
		return (0);
	if (str[0] == '|' || str[0] == '&')
		return (error_msg(ft_substr(str, 0, 1), NO_EXIT, 2), 2);
	i = -1;
	while (str[++i])
	{
		if (!check_line2(str, &i))
			return (2);
		if (str[i] == '|' || str[i] == '&')
			if (!check_pipe(&str[i]))
				return (2);
		if (forbidden_c(str[i]))
			return (error_msg2(ft_substr(str, i, 1), NO_EXIT, 2), 2);
	}
	return (1);
}
