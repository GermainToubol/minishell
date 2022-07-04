/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 03:33:06 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/04 22:11:17 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include "expand.h"
#include "libft.h"
#include "utils.h"

// int expand_wc(char *cmd)
// {
// 	t_list	**wc_lst;
// 	char	**ret;

// 	wc_lst = ft_calloc(1, sizeof(t_list *));
// 	if (!wc_lst)
// 		return (display_error("Error allcation\n", 0), NULL);
// 	if (wildcards(cmd, wc_lst))
// 	{
// 		ft_lstclear(wc_lst, del_node_wc);
// 		return (free(wc_lst), NULL);
// 	}
// 	if (*wc_lst)
// 	{
// 		ret = do_wildcard_content(wc_lst);
// 		ft_lstclear(wc_lst, del_node_wc);
// 	}
// 	else
// 		ret = do_basic(cmd);
// 	free(wc_lst);
// 	return (ret);
// }
