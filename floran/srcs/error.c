/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:06:03 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/10 17:27:15 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "floran.h"

void	error_msg(char *err, int do_exit, int signal)
{
	ft_fprintf(2, "bash: syntax error near unexpected token `");
	if (ft_atoll(err) > MAX_INT)
		ft_fprintf(2, "newline");
	else
		ft_fprintf(2, "%s", err);
	ft_fprintf(2, "'\n");
	free(err);
	if (do_exit == 1)
		exit(signal);
}

void	error_msg2(char *err, int do_exit, int signal)
{
	ft_fprintf(2, "bash: not to handle `");
	ft_fprintf(2, "%s", err);
	ft_fprintf(2, "'\n");
	free(err);
	if (do_exit == 1)
		exit(signal);
}
