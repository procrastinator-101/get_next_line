/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yarroubi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 17:13:02 by yarroubi          #+#    #+#             */
/*   Updated: 2021/01/25 18:24:19 by yarroubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_file	*get_current_file(t_file *files_tail, int fd)
{
	t_file	*current_file;

	while (files_tail)
	{
		if (files_tail->fd == fd)
			return (files_tail);
		files_tail = files_tail->next;
	}
	current_file = malloc(t_file);
	if (!current_file)
		return (0);
	current_file->fd = fd;
	current_file->start = 0;
	current_file->next = 0;
	current_file->previous = files_tail;
	files_tail->next = current_file;
	return (current_file);
}

static int	destroy_file(t_file *file, int ret)
{
	if (file->previous)
		file->previous->next = file->next;
	if (file->next)
		file->next->previous = file->previous;
	free(file);
	return (ret);
}

static int	update_line(t_file *file, char **line, int dst_size, int src_size)
{
	char	*str;

	str = malloc((dst_size + !(dst_size) + src_size) * sizeof(char));
	if (!str)
	{
		free(*line);
		*line = 0;
		return (-1);
	}
	ft_strfncpy(str, line, '\n', dst_size);
	ft_strfncpy(str + dst_size - !(dst_size), file->buffer + file->start, \
		'\n', src_size);
	free(*line);
	*line = 0;
	return (dst_size + !(dst_size) + src_size);
}

int get_next_line(int fd, char **line)
{
	int				ret;
	int				size;
	char			*str;
	t_file			*current_file;
	static t_file	*files;

	if (!line || BUFFER_SIZE < 1 || fd < 0)
		return (-1);
	*line = 0;
	size = 0;
	current_file = get_current_file(files, fd);
	if (!current_file)
		return (-1);
	while (1)
	{
		ret = read(current_file->fd, current_file->buffer, BUFFER_SIZE);
		if (ret < 1)
			return (destroy_file(current_file, ret));
		ret = update_line(current_file, line, size, ret);
		if (ret == -1)
			return (destroy_file(current_file, ret));
		size = ret;
	}
}
