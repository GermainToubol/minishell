/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 07:13:19 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/07 01:00:02 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

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
	P_END,
	CMD
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
int			lexer(char *line, t_tokens *tokens);
int			is_redirect(char *line, t_lxm *lxm, t_tokens *tokens);
int			is_separator(char *line, t_lxm *lxm, t_tokens *tokens);
int			is_word(char *line, t_lxm *lxm, t_tokens *tokens);
int			is_prio(char *line, t_lxm *lxm, t_tokens *tokens);
int			c_separator(char c);

//ALLOC
int			tokens_alloc(t_tokens *tokens);

//HDOC
int			set_hdoc(char **hdoc);
char		*quotes_hdoc(const char *cmd);
char		*tmp_filename(void);
char		*tmp_filename_q(void);

#endif