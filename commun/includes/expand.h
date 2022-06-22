/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 17:07:13 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/22 03:57:04 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# define TAB_BUFFER 4096

void	free_ptr(void *data);
char	**do_expand(char **cmd);
char	**expand_loop_end(char **new_cmd, size_t *size,
			size_t *max);
char	**expand_loop_realloc(char **new_cmd, size_t *size,
			size_t *max);
char	**expand_loop_wildcard(char **new_cmd, char *cmd,
			size_t *size, size_t *max);
char	**do_wildcard(char *cmd, char ***new_cmd,
			size_t *size, size_t *max);

#endif