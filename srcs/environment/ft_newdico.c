/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_newdico.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 10:07:38 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/16 10:53:43 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"
#include "g_minishell.h"

/**
   Initialise a ney dictionnary entry.

   @input: the dictionnary entry formated as `KEY[=VALUE]`. The second
   part is optional and the value will be initialized as NULL if none
   is given.

   @output: the new key/value pair in a t_dico format if it
   successes. NULL otherwise.
*/

t_dico	*ft_newdico(char *entry)
{
	t_dico	*tmp;
	size_t	i;

	tmp = ft_calloc(1, sizeof(*tmp));
	if (tmp == NULL)
		return (NULL);
	i = 0;
	while (entry[i] != '\0' && entry[i] != '=')
		i++;
	tmp->key = ft_substr(entry, 0, i);
	if (entry[i] == '=')
		tmp->value = ft_substr(entry, i + 1, ft_strlen(entry));
	if (tmp->key == NULL || (tmp->value == NULL && entry[i] == '=' ))
	{
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		return (NULL);
	}
	return (tmp);
}
