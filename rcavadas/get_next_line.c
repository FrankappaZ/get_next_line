/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcavadas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/20 19:07:19 by rcavadas          #+#    #+#             */
/*   Updated: 2016/03/10 21:42:13 by rcavadas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	treat_extract(char **line, char **extract)
{
	int	index;

	index = 0;
	while (extract[0][index])
	{
		if (extract[0][index] == '\n')
		{
			*line = ft_strsub(*extract, 0, index);
			*extract = ft_strsub(*extract, index + 1, ft_strlen(*extract) -
					ft_strlen(*line));
			return (1);
		}
		index++;
	}
	return (0);
}

int	get_next_line(int const fd, char **line)
{
	char		buf[BUFF_SIZE + 1];
	int			ret;
	static char	*extract = NULL;

	if (extract && (treat_extract(line, &extract)))
		return (1);
	ret = read(fd, buf, BUFF_SIZE);
	if (ret > 0)
	{
		buf[ret] = '\0';
		extract = ft_strjoin(extract, buf);
	}
	if (ret == 0 && (extract && ft_strlen(extract) > 0))
	{
		*line = ft_strdup(extract);
		ft_strdel(&extract);
		return (1);
	}
	if (ret == 0)
		return (0);
	if (ret < 0)
		return (-1);
	return (get_next_line(fd, line));
}
