/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 23:20:06 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/10 17:38:49 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "floran.h"

static char	*check_cmd(t_cmd *data, char *cmd)
{
	unsigned int	i;
	size_t			len;
	char			*ret;

	data->inputs = split_red(cmd, "<");
	data->outputs = split_red(cmd, ">");
	i = first_cmd(cmd, 0, &len);
	if (i == ft_strlen(cmd))
		ret = ft_strdup("");
	else
		ret = ft_substr(cmd, i, len);
	return (ret);
}

static void	fill_cmd_strct2(t_cmd **data, char **path, char *cmd, char **tmp)
{
	if (is_empty(cmd))
	{
		*tmp = check_cmd(*data, cmd);
		(*data)->cmd = ft_split(*tmp, '\0');
		(*data)->path_exec = NULL;
	}
	else
	{
		*tmp = check_cmd(*data, cmd);
		if (*tmp[0] == '\0')
		{
			(*data)->cmd = ft_split(*tmp, '\0');
			(*data)->path_exec = NULL;
		}
		else
		{
			(*data)->cmd = ft_split(*tmp, ' ');
			(*data)->path_exec = check_path(path, (*data)->cmd[0]);
		}
	}
}

t_cmd	*fill_cmd_strct(char **path, char *cmd)
{
	t_cmd	*data;
	char	*trim_cmd;

	data = (t_cmd *)malloc(sizeof(t_cmd));
	if (!data)
		return (NULL);
	fill_cmd_strct2(&data, path, cmd, &trim_cmd);
	if (trim_cmd)
		free(trim_cmd);
	return (data);
}

static char	*fill_red(char *str, char *sep, t_redirect *ret)
{
	if (is_sep(*str, sep) && sep[0] == '>')
	{
		ret->append = IS_APPEND;
		str++;
	}
	else
		ret->append = NO_APPEND;
	if (is_sep(*str, sep) && sep[0] == '<')
	{
		ret->heredoc = IS_HEREDOC;
		str++;
	}
	else
		ret->heredoc = NO_HEREDOC;
	while (ft_iswhitspaces(*str))
		str++;
	return (str);
}

t_redirect	*fill_redirect(char *str, char *sep, char *out)
{
	int			j;
	t_redirect	*ret;

	ret = (t_redirect *)ft_calloc(1, sizeof(t_redirect));
	if (!ret)
		return (free(out), NULL);
	ret->out = ft_atoi(out);
	free(out);
	str = fill_red(str, sep, ret);
	j = 0;
	if (sep[0] == '<' && *str == '>')
	{
		j++;
		while (ft_iswhitspaces(str[j]))
			j++;
	}
	while (str[j] && !ft_iswhitspaces(str[j])
		&& str[j] != '<' && str[j] != '>')
		j++;
	ret->file = ft_strndup(str, j);
	if (!ret->file)
		return (free(ret), NULL);
	return (ret);
}
