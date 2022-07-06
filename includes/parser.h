/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:50:43 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/07 01:01:13 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <unistd.h>
# include <stdlib.h>
# include "lexer.h"
# include "minishell.h"

# define L_PATH 5

typedef struct s_parse
{
	t_token	type;
	t_cmd	*cmd;
}	t_parse;

//PARSE
int			check_path(char **path, char *cmd, char **dest);
int			fill_cmd_line(t_tokens *tokens,
				t_parse **cmd_line, size_t size);
char		**fill_cmdn(t_tokens *tokens, size_t start,
				size_t max, int *err);
t_parse		**parser(t_tokens *tokens);
t_redirect	**fill_redirect(t_tokens *tokens, size_t start,
				size_t max, int *err);

//Display
void		print_node(t_cmd *data);
void		show_red(t_redirect **red);
void		print_tab(char **tab);

#endif