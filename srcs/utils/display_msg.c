/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_msg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:13:15 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/15 16:52:29 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

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

void	display_error_red(char *err, int i)
{
	char	*err_n;

	if (err)
	{
		if (i > 1)
			i--;
		err_n = ft_substr(err, 0, i);
		if (!err_n)
			return (display_error("Error allocation\n", 0));
		ft_fprintf(2, "minishell: syntax error"
			" near unexpected token `%s'\n", err_n);
		free(err_n);
	}
}
