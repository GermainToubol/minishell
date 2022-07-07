/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_msg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:13:15 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/07 23:00:25 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"
#include "g_minishell.h"

void	error_alloc(void)
{
	ft_fprintf(2, "minishell: Cannot allocate memory\n");
	set_status(12);
}

void	error_msg(char *err, int status)
{
	ft_fprintf(2, "%s", err);
	set_status(status);
}

void	error_syntax(char c)
{
	if (c == '\n')
		ft_fprintf(2, "minishell: syntax error"
			" near unexpected token `newline'\n");
	else
		ft_fprintf(2, "minishell: syntax error"
			" near unexpected token `%c'\n", c);
	set_status(2);
}

void	error_syntax_str(char *err, int i)
{
	char	*err_n;

	if (err)
	{
		if (i > 1)
			i--;
		err_n = ft_substr(err, 0, i);
		if (!err_n)
			return (error_alloc());
		ft_fprintf(2, "minishell: syntax error"
			" near unexpected token `%s'\n", err_n);
		free(err_n);
	}
	set_status(2);
}
