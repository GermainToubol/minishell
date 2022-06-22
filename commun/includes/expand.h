/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 17:07:13 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/22 13:32:30 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# define TAB_BUFFER 4096

void	free_ptr(void *data);
char	**do_expand(char **cmd);
char	**expand_loop_end(char ***new_cmd);
int		expand_loop_wildcard(char ***new_cmd, char *cmd, size_t i);
char	**do_wildcard(char *cmd);
char	**do_basic(char *cmd);

#endif