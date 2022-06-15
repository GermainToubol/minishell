/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 17:47:10 by gtoubol           #+#    #+#             */
/*   Updated: 2022/05/12 14:30:37 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	prod;
	void	*new;

	prod = nmemb * size;
	if (nmemb && size && (prod / size != nmemb || prod / nmemb != size))
		return (NULL);
	new = malloc(nmemb * size);
	if (new)
		ft_bzero(new, prod);
	return (new);
}
