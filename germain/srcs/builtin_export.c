/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 17:02:00 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/16 18:56:54 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"
#include "g_minishell.h"

static int		show_export(t_list	*env);
static size_t	export_check_name(char *name);
static int		export_set_value(t_list **env, char *name, size_t i);

int	builtin_export(int argc, char **argv, t_list **env)
{
	int		i;
	size_t	j;
	int		re;

	if (argc == 1)
		return (show_export(*env));
	i = 1;
	re = 0;
	while (i < argc)
	{
		j = export_check_name(argv[i]);
		if (j == 0)
		{
			re = 1;
			ft_fprintf(2, "minishell: export: `%s': not a valid identifier\n",
				argv[i]);
		}
		else
		{
			if (export_set_value(env, argv[i], j) != 0)
				re = 1;
		}
		i++;
	}
	return (re);
}

static int	show_export(t_list	*env)
{
	t_dico	*dico;

	while (env != NULL)
	{
		dico = (t_dico *)env->content;
		if (dico->value == NULL)
			ft_printf("declare -x %s\n", dico->key);
		else
			ft_printf("declare -x %s=\"%s\"\n", dico->key, dico->value);
		env = env->next;
	}
	return (0);
}

static size_t	export_check_name(char *name)
{
	size_t	i;

	i = 0;
	while (name[i] != '\0' && (ft_isalnum(name[i]) || name[i] == '_'))
		i++;
	if (i != 0 && (name[i] == '\0' || name[i] == '='
			|| (name[i] == '+' && name[i + 1] == '=')))
		return (i);
	return (0);
}

static t_list	*export_list(t_list **env, char *name_tmp, char *new_name)
{
	char	*content;
	t_list	*tmp;

	content = environment_get(*env, name_tmp);
	if (content == NULL)
	{
		tmp = environment_add(env, name_tmp);
		if (tmp != NULL
			&& environment_set(*env, name_tmp, new_name) == 1)
			tmp = NULL;
	}
	else
	{
		content = ft_strjoin(content, new_name);
		if (content == NULL
			|| environment_set(*env, name_tmp, content) == 1)
			tmp = NULL;
		free(content);
	}
	return (tmp);
}

static int	export_set_value(t_list **env, char *name, size_t i)
{
	t_list	*tmp;
	char	*name_tmp;

	if (name[i] == '\0' && name[i] == '=')
		tmp = environment_add(env, name);
	else if (name[i] == '+')
	{
		name_tmp = ft_substr(name, 0, i);
		if (name == NULL)
		{
			return (1);
		}
		tmp = export_list(env, name_tmp, name + i + 1);
	}
	if (tmp == NULL)
	{
		ft_fprintf(2, "minishell: export: memory allocation failure\n");
		return (1);
	}
	return (0);
}
