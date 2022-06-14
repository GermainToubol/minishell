/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 07:13:19 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/14 17:54:35 by fmauguin         ###   ########.fr       */
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
	AMPERSAND,
	OR,
	AND
}	t_token;

typedef struct s_lxm
{
	char	*data;
	t_token	type;
}	t_lxm;

typedef struct s_tokens
{
	t_lxm	tokens[BUFFER_LXM];
	size_t	size;
	size_t	max;
}	t_tokens;

//LEXER
int			is_redirect(char *line, t_lxm *lxm, t_tokens *tokens);
int			is_separator(char *line, t_lxm *lxm, t_tokens *tokens);
int			is_word(char *line, t_lxm *lxm, t_tokens *tokens);

//DEBUG
void		print_tokens(t_tokens *tokens);

//UTILS
char		*ft_strndup(char *src, size_t len);
void		display_error(char *err, char c);
long long	ft_atoll(char *s);

#endif