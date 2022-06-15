/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:50:43 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/15 16:51:26 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <unistd.h>
# include <stdlib.h>
# include "lexer.h"
# include "utils.h"

# define L_PATH 5

//PARSE
int		parser(t_tokens *tokens, char **env);
char	*check_path(char **path, char *cmd);

//PATH
char	**get_path(char **env);

//FREE

//DEBUG

#endif