/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 07:13:19 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/15 16:51:14 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "utils.h"

# define BUFFER_LXM 4096

typedef enum e_token
{
	WORD,
	IO_IN,
	IO_OUT,
	IO_HDOC,
	IO_APP,
	PIPE,
	OR,
	AND,
	P_START,
	P_END
}	t_token;

typedef struct s_lxm
{
	char	*data;
	t_token	type;
}	t_lxm;

typedef struct s_tokens
{
	t_lxm	*tokens;
	size_t	size;
	size_t	max;
}	t_tokens;

//LEXER
int			is_redirect(char *line, t_lxm *lxm, t_tokens *tokens);
int			is_separator(char *line, t_lxm *lxm, t_tokens *tokens);
int			is_word(char *line, t_lxm *lxm, t_tokens *tokens);
int			lexer(char *line, t_tokens *tokens);
int			is_prio(char *line, t_lxm *lxm, t_tokens *tokens);

//ALLOC
int			tokens_alloc(t_tokens *tokens);

//DEBUG
void		print_tokens(t_tokens *tokens);
void		print_lexer(char *line, t_tokens *tokens);

//FREE
void		free_lxm(t_lxm *lxm, size_t size);

#endif