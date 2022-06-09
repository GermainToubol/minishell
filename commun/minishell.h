/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:14:28 by gtoubol           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/06/09 21:41:42 by fmauguin         ###   ########.fr       */
=======
/*   Updated: 2022/06/09 19:15:48 by gtoubol          ###   ########.fr       */
>>>>>>> refs/remotes/origin/master
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
typedef struct s_redirect
{
	char	*file;
	int		out;
	int		heredoc;
	int		append;
}	t_redirect;

typedef struct s_redirect
{
	char	*file;
	int		out;
	int		heredoc;
	int		append;
}	t_redirect;

typedef struct s_cmd
{
	char		*input;
	char		*path_exec;
	char		**cmd;
	t_redirect	**outputs;
}	t_cmd;

# define IS_HEREDOC 1
# define NO_HEREDOC 0
# define IS_APPEND 1
# define NO_APPEND 0

#endif
