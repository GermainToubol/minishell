/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_filename.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 01:26:33 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/30 01:39:38 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "libft.h"
#include "utils.h"

static int	tmp_filename_loop(int i, char *filename)
{
	while (filename[i] == '9')
		filename[i--] = '0';
	if (i < 13)
		return (1);
	while (ft_isdigit(filename[i]))
		i++;
	i--;
	filename[i] = filename[i] + 1;
	return (0);
}

char	*tmp_filename(void)
{
	char	tmp_file[21];
	int		i;
	char	*ret;

	i = -1;
	ret = "/tmp/sh-thd-00000000";
	while (ret[++i])
		tmp_file[i] = ret[i];
	tmp_file[i--] = 0;
	while (!access(tmp_file, F_OK))
		if (tmp_filename_loop(i, tmp_file))
			return (NULL);
	ret = ft_strdup(tmp_file);
	if (!ret)
		display_error("Error allocation\n", 0);
	return (ret);
}

char	*tmp_filename_q(void)
{
	char	tmp_file[22];
	int		i;
	char	*ret;

	i = -1;
	ret = "/tmp/sh-thd-00000000q";
	while (ret[++i])
		tmp_file[i] = ret[i];
	tmp_file[i--] = 0;
	i--;
	while (!access(tmp_file, F_OK))
		if (tmp_filename_loop(i, tmp_file))
			return (NULL);
	ret = ft_strdup(tmp_file);
	if (!ret)
		display_error("Error allocation\n", 0);
	return (ret);
}
