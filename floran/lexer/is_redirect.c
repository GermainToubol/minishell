/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 16:50:22 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/14 21:40:15 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

static void	display_error_red(char *err, int i)
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

static int	is_redirect_out(char *line, t_lxm *lxm, t_tokens *tokens, int *i)
{
	*i += 1;
	if (tokens->size > 0 && (tokens->tokens[tokens->size - 1].type >= IO_IN
			&& tokens->tokens[tokens->size - 1].type <= IO_APP))
		return (display_error_red(line, *i), 1);
	lxm->type = IO_OUT;
	if (line[*i] == '>')
	{
		*i += 1;
		lxm->type = IO_APP;
	}
	lxm->data = ft_strndup(line, *i);
	if (!lxm->data)
		return (display_error("Error allocation\n", 0), 1);
	tokens->size++;
	return (0);
}

static int	is_redirect_in(char *line, t_lxm *lxm, t_tokens *tokens, int *i)
{
	*i += 1;
	if (tokens->size > 0 && (tokens->tokens[tokens->size - 1].type >= IO_IN
			&& tokens->tokens[tokens->size - 1].type <= IO_APP))
		return (display_error_red(line, *i), 1);
	lxm->type = IO_IN;
	if (line[*i] == '<')
	{
		*i += 1;
		lxm->type = IO_HDOC;
	}
	lxm->data = ft_strndup(line, *i);
	if (!lxm->data)
		return (display_error("Error allocation\n", 0), 1);
	tokens->size++;
	return (0);
}

int	is_redirect(char *line, t_lxm *lxm, t_tokens *tokens)
{
	int	i;

	i = 0;
	while (ft_isdigit(line[i]))
		i++;
	if (line[i] == '>')
	{
		if (is_redirect_out(line, lxm, tokens, &i))
			return (-1);
	}
	else if (line[i] == '<')
	{
		if (is_redirect_in(line, lxm, tokens, &i))
			return (-1);
	}
	return (i);
}
