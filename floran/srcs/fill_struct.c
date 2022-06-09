/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 23:20:06 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/09 23:41:21 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "floran.h"

static char	*redirect_c(char *cmd, char c)
{
	int	i;
	int	j;

	i = ft_strlen(cmd) - 1;
	while (i > 0 && cmd[i] != c)
		i--;
	if (cmd[i++] == c)
	{
		while (ft_iswhitspaces(cmd[i]))
			i++;
		j = 0;
		while (!ft_iswhitspaces(cmd[i + j]) && cmd[i + j])
			j++;
		return (ft_strndup(&cmd[i], j));
	}
	return (NULL);
}

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

	data->input = redirect_c(cmd, '<');
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
	if (!trim_cmd)
		return (NULL);
	data->cmd = ft_split(trim_cmd, ' ');
	free(trim_cmd);
	if (!data->cmd)
		return (NULL);
	data->path_exec = check_path(path, data->cmd[0]);
	return (data);
}

t_redirect	*fill_redirect(char *str, char *sep, char *out)
{
	int			j;
	t_redirect	*ret;

	ret = (t_redirect *)ft_calloc(1, sizeof(t_redirect));
	if (!ret)
		return (NULL);
	ret->out = ft_atoi(out);
	free(out);
	if (is_sep(*str, sep))
	{
		ret->append = IS_APPEND;
		str++;
	}
	else
		ret->append = NO_APPEND;
	ret->heredoc = NO_HEREDOC;
	while (ft_iswhitspaces(*str))
		str++;
	j = 0;
	while (!ft_iswhitspaces(str[j]) && str[j] != '<' && !is_sep(str[j], sep))
		j++;
	ret->file = ft_strndup(str, j);
	if (!ret)
		return (NULL);
	return (ret);
}
