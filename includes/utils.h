/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:50:17 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/03 18:58:34 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include "libft.h"
# include "lexer.h"
# include "parser.h"

void	display_error_red(char *err, int i);
void	display_error(char *err, char c);
void	print_tokens(t_tokens *tokens);
void	print_lexer(char *line, t_tokens *tokens);
void	free_lxm(t_lxm *lxm, size_t size);
void	free_parse(t_parse **parse);
void	free_cmd(t_cmd	*tmp);
void	free_red(t_redirect **tab);
void	free_tab(char **tab);
void	print_cmd_line(t_parse **parse);
void	print_cmd_line_detail(t_parse **parse);
void	ft_list_remove_if(t_list **begin_list, void *data_ref,
			int (*cmp)(), void (*free_fct)(void *));
void	quicksort(char **tab, size_t len);

int		ft_strcmp(const char *s1, const char *s2);
int		last_char(char *s, char c);
char	**tab_realloc(char **tab, int i, size_t size,
			size_t buffer_size);

char	*ft_strndup(char *src, size_t len);
char	*ft_join3(char *s1, char *s2, char *s3);

char	**lst_to_tab(t_list **lst);

size_t	size_tab(char **tab);
int		cpy_tab(char **from, char **to, size_t size);

int		ft_atoll(char *s, long long *n);
int		strjoin_custom(char **dest, char *src);

int		del_hdoc_token(t_tokens *tokens);
int		del_hdoc_parse(t_parse **parse);
char	**ft_join_tab(char **tab1, size_t size1, char **tab2, size_t size2);

#endif
