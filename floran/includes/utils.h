/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:50:17 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/15 22:32:09 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include "libft.h"
# include "lexer.h"
# include "parser.h"

void		display_error_red(char *err, int i);
void		display_error(char *err, char c);
void		print_tokens(t_tokens *tokens);
void		print_lexer(char *line, t_tokens *tokens);
void		free_lxm(t_lxm *lxm, size_t size);
void		free_parse(t_parse **parse);
void		free_cmd(t_cmd	*tmp);
void		free_red(t_redirect **tab);
void		free_tab(char **tab);

char		*ft_strndup(char *src, size_t len);
char		*ft_join3(char *s1, char *s2, char *s3);

long long	ft_atoll(char *s);

#endif