/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:14:28 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/16 13:07:23 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
  no input or pipe: NULL
  no output or pipe: NULL
  no errput: NULL
  bad cmd : ->path_exec=NULL and ->cmd=cmd
  out : stdout ou stderr 1 ou 2
*/
typedef enum e_io
{
	IN,
	OUT,
	HDOC,
	APP
}	t_eio;

typedef struct s_redirect
{
	char	*file;
	int		fd;
	t_eio	io_r;
}	t_redirect;

typedef struct s_cmd
{
	char		*path_exec;
	char		**cmd;
	t_redirect	**redirect;
}	t_cmd;

# define IS_HEREDOC 1
# define NO_HEREDOC 0
# define IS_APPEND 1
# define NO_APPEND 0

#endif
