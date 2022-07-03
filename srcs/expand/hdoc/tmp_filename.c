/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_filename.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 01:26:33 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/30 11:41:37 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "libft.h"
#include "utils.h"

static int	tmp_filename_loop(int i, char *filename)
{
	while (!access(filename, F_OK))
	{
		while (filename[i] == '9')
			filename[i--] = '0';
		if (i < 13)
			return (1);
		filename[i] = filename[i] + 1;
	}
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
	if (tmp_filename_loop(i, tmp_file))
		return (NULL);
	ret = ft_strdup(tmp_file);
	if (!ret)
		return (display_error("Error allocation\n", 0), NULL);
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
	if (tmp_filename_loop(i, tmp_file))
		return (NULL);
	ret = ft_strdup(tmp_file);
	if (!ret)
		return (display_error("Error allocation\n", 0), NULL);
	return (ret);
}
