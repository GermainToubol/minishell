/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:50:43 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/16 01:05:00 by fmauguin         ###   ########.fr       */
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
int			parser(t_tokens *tokens, char **env);
char		*check_path(char **path, char *cmd);
t_redirect	**fill_redirect(t_tokens *tokens, size_t start, size_t i);
char		**fill_cmdn(t_tokens *tokens, size_t start, size_t max);

//PATH
char		**get_path(char **env);

//FREE

//DEBUG

#endif