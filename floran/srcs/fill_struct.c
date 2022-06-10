/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 23:20:06 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/10 11:43:00 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "floran.h"

static unsigned int	first_cmd(char *cmd, unsigned int i, size_t *len)
{
	*len = 0;
	while (ft_iswhitspaces(cmd[i]))
		i++;
	while (ft_isdigit(cmd[i]))
		i++;
	if (cmd[i] == '<' || cmd[i] == '>')
	{
		i++;
		while (ft_iswhitspaces(cmd[i]))
			i++;
		while (cmd[i] && !ft_iswhitspaces(cmd[i]) && cmd[i] != '<'
			&& cmd[i] != '>')
			i++;
		return (first_cmd(cmd, i, len));
	}
	else
	{
		while (i > 0 && ft_isdigit(cmd[i]))
			i--;
		while (cmd[i + *len] && cmd[i + *len] != '<' && cmd[i + *len] != '>')
			(*len)++;
		return (i);
	}
}

static char	*check_cmd(t_cmd *data, char *cmd)
{
	unsigned int	i;
	size_t			len;
	char			*ret;

	data->inputs = split_red(cmd, "<");
	data->outputs = split_red(cmd, ">");
	i = first_cmd(cmd, 0, &len);
	ret = ft_substr(cmd, i, len);
	if (!ret)
		return (NULL);
	return (ret);
}

t_cmd	*fill_cmd_strct(char **path, char *cmd)
{
	t_cmd	*data;
	char	*trim_cmd;

	data = (t_cmd *)malloc(sizeof(t_cmd));
	if (!data)
		return (NULL);
	trim_cmd = check_cmd(data, cmd);
	data->cmd = ft_split(trim_cmd, ' ');
	if (trim_cmd)
		free(trim_cmd);
	data->path_exec = check_path(path, data->cmd[0]);
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
	if (sep[0] == '<' && *str == '>')
		str++;
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
	while (str[j] && !ft_iswhitspaces(str[j])
		&& str[j] != '<' && str[j] != '>')
		j++;
	ret->file = ft_strndup(str, j);
	if (!ret->file)
		return (free(ret), NULL);
	return (ret);
}
