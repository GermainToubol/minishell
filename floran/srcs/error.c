/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:06:03 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/09 17:33:58 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "floran.h"

void	error_msg(char *err, int do_exit, int signal)
{
	ft_fprintf(2, "bash: %s\n", err);
	if (do_exit == 1)
		exit(signal);
}
