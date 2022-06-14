/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:40:11 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/14 19:47:56 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include "lexer.h"

void	display_error(char *err, char c)
{
	if (err)
		ft_putstr_fd(err, 2);
	else if (c != 0 && c == '\n')
		ft_fprintf(2, "minishell: syntax error"
			" near unexpected token `newline'\n");
	else
		ft_fprintf(2, "minishell: syntax error"
			" near unexpected token `%c'\n", c);
}

void	print_tokens(t_tokens *tokens)
{
	size_t	i;

	i = 0;
	while (i < tokens->size)
	{
		ft_printf("\nElement: %i\n", i);
		ft_printf("data: %s\n", tokens->tokens[i].data);
		ft_printf("type: %i\n", tokens->tokens[i].type);
		i++;
	}
}

char	*ft_strndup(char *src, size_t len)
{
	char	*r;
	size_t	i;

	if (!src)
		return (NULL);
	r = (char *)malloc((len + 1) * sizeof(char));
	if (!r)
		return (NULL);
	i = 0;
	while (i < len)
	{
		r[i] = src[i];
		i++;
	}
	r[i] = '\0';
	return (r);
}

long long	ft_atoll(char *s)
{
	long long	n;
	int			minus;

	minus = 1;
	n = 0;
	if (!s)
		return (0);
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			minus = -1;
		s++;
	}
	while (ft_isdigit(*s))
	{
		n += *s - '0';
		n *= 10;
		s++;
	}
	return (n * minus);
}
