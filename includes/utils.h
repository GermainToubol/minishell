/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:50:17 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/07 00:39:12 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stddef.h>
# include "libft.h"
# include "lexer.h"
# include "parser.h"

//Display
void	display_error_red(char *err, int i);
void	display_error(char *err, char c);
void	print_tokens(t_tokens *tokens);
void	print_lexer(char *line, t_tokens *tokens);
void	print_cmd_line(t_parse **parse);
void	print_cmd_line_detail(t_parse **parse);
void	print_node_str(void *data);
void	debug_gnl(const char *s1, char *s2, int i);

//Free
void	free_lxm(t_lxm *lxm, size_t size);
void	free_parse(t_parse **parse);
void	free_parse_nohdoc(t_parse **parse);
void	free_cmd(t_cmd	*tmp);
void	free_red(t_redirect **tab);
void	free_tab(char **tab);
void	free_lst_str(t_list **lst);
void	ft_list_remove_at(t_list **begin_list, unsigned int nb,
			void (*free_fct)(void *));
void	del_node_str(void *data);
int		del_hdoc_token(t_tokens *tokens);
int		del_hdoc_parse(t_parse **parse);

//str
int		ft_strcmp(const char *s1, const char *s2);
int		strjoin_custom(char **dest, char *src);
int		clean_backslash(char **s);
int		add_backslash(char **s);
int		ft_atoll(char *s, long long *n);
char	*add_backslash_safe(char *s);
char	*ft_strndup(char *src, size_t len);
char	*ft_join3(char *s1, char *s2, char *s3);
char	*trim_c(char *s, char c);
size_t	last_char(char *s, char c);
size_t	skip_quote(const char *line);

//tab
size_t	size_tab(char **tab);

//listes
void	sort_list(t_list **lst);
char	**lst_to_tab_str(t_list **lst);
int		cat_lst(t_list **dest, t_list **src);
int		clean_backslash_expand(char *s, t_list *index);
int		strjoin_custom_lst(void **dest, char *src);
t_list	*ft_list_at(t_list *begin_list, unsigned int nbr);
#endif