/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 17:49:03 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/30 18:39:34 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expand.h"
#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	char	*var;
	char	*line;

	var = NULL;
	line = readline("line: ");
	if (ft_strchr(line, '\'') || ft_strchr(line, '"'))
		var = expand_quotes(line);
	else if (ft_strchr(line, '$'))
		var = expand_var(line);
	ft_printf("\nret: %s\n", var);
	free(var);
	free(line);
	return (0);
}
