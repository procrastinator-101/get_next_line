/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yarroubi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 17:13:02 by yarroubi          #+#    #+#             */
/*   Updated: 2021/10/20 13:58:14 by yarroubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_file	*get_current_file(t_file **files, int fd)
{
	t_file	*current;

	current = ft_file_find(*files, fd);
	if (current)
		return (current);
	current = ft_file_create(fd);
	if (!current)
		return (current);
	ft_file_addfront(files, current);
	return (current);
}

static char	*ft_initialise_str(char **line, int size, int new_size)
{
	char	*str;

	str = malloc(new_size * sizeof(char));
	if (!str)
	{
		free(*line);
		*line = 0;
		return (0);
	}
	ft_memcpy(str, *line, size);
	return (str);
}

static int	update_line(t_file *file, char **line, int size)
{
	int		i;
	int		new_size;
	char	*str;

	i = file->start;
	while (file->buffer[i] && file->buffer[i] != '\n')
		i++;
	if (size)
		size--;
	new_size = size + i + 1 - file->start;
	str = ft_initialise_str(line, size, new_size);
	if (!str)
		return (-1);
	ft_memcpy(str + size, file->buffer + file->start, new_size - size);
	if (!file->buffer[i] || !file->buffer[i + 1])
		file->start = 0;
	else
		file->start += new_size - size;
	free(*line);
	*line = str;
	return (new_size);
}

static int	ft_fill_line(char **line, t_file **files, t_file *current_file, \
			int *size)
{
	int	ret;

	if (!current_file->start)
	{
		ret = read(current_file->fd, current_file->buffer, BUFFER_SIZE);
		if (ret > 0)
			current_file->buffer[ret] = 0;
		else
		{
			ft_file_remove(files, current_file->fd);
			return (ret);
		}
	}
	*size = update_line(current_file, line, *size);
	if (current_file->start >= BUFFER_SIZE)
		current_file->start = 0;
	if ((*line)[*size - 1] == '\n')
	{
		(*line)[*size - 1] = 0;
		return (1);
	}
	return (RET_SUCCESS);
}

int	get_next_line(int fd, char **line)
{
	int				ret;
	int				size;
	t_file			*current_file;
	static t_file	*files;

	if (!line || BUFFER_SIZE < 1 || fd < 0)
		return (-1);
	*line = 0;
	size = 0;
	current_file = get_current_file(&files, fd);
	if (!current_file)
		return (-1);
	ret = RET_SUCCESS;
	while (ret == RET_SUCCESS)
		ret = ft_fill_line(line, &files, current_file, &size);
	return (ret);
}
