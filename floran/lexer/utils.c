/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:40:11 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/15 12:39:17 by fmauguin         ###   ########.fr       */
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

void	print_lexer(char *line, t_tokens *tokens)
{
	size_t		i;
	const char	*e_type[] = {"WORD", "IO_IN", "IO_OUT",
		"IO_HDOC", "IO_APP", "PIPE", "OR", "AND", "P_START", "P_END"};
	const char	*e_colors[] = {"\x1b[32m", "\x1b[34m", "\x1b[94m",
		"\x1b[35m", "\x1b[95m", "\x1b[33m", "\x1b[93m", "\x1b[93m",
		"\x1b[31m", "\x1b[91m"};

	i = 0;
	ft_printf("\nOrigine:\n%s\n", line);
	ft_printf("Lexer:\n");
	while (i < tokens->size)
	{
		ft_printf("%s", e_colors[tokens->tokens[i].type]);
		ft_printf("%s", e_type[tokens->tokens[i].type]);
		ft_printf("\x1b[0m ");
		i++;
	}
	ft_printf("\n\n");
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
