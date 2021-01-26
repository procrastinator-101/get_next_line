/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yarroubi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 17:13:02 by yarroubi          #+#    #+#             */
/*   Updated: 2021/01/26 20:31:52 by youness          ###   ########.fr       */
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
	current_file = malloc(sizeof(t_file));
	if (!current_file)
		return (0);
	current_file->fd = fd;
	current_file->start = 0;
	current_file->next = 0;
	current_file->previous = files_tail;
	if (files_tail)
		files_tail->next = current_file;
	return (current_file);
}

static int		destroy_file(t_file *file, int ret)
{
	if (file->previous)
		file->previous->next = file->next;
	if (file->next)
		file->next->previous = file->previous;
	free(file);
	return (ret);
}

static int		update_line(t_file *file, char **line, int dst_size, \
				int src_len)
{
	int		size;
	int		offset;
	char	*str;

	size = -1;
	while (++size < src_len && file->buffer[file->start + size] != '\n')
		size++;
	size += file->buffer[file->start + size] == '\n';
	str = malloc((dst_size + !(dst_size) + size) * sizeof(char));
	if (!str)
	{
		free(*line);
		*line = 0;
		return (-1);
	}
	ft_strfcpy(str, *line, dst_size);
	offset = dst_size ? dst_size - 1 : 0;
	ft_strfcpy(str + offset, file->buffer + file->start, size);
	free(*line);
	*line = str;
	return (dst_size + !(dst_size) + size);
}

int				get_next_line(int fd, char **line)
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
		printf("start     = %d\n", current_file->start);
		if (current_file->start)
			ret =  update_line(current_file, line, size, BUFFER_SIZE - current_file->start);
		else
			ret = read(current_file->fd, current_file->buffer, BUFFER_SIZE);
		printf("ret = %d\n", ret);
		//printf("line = |%s|\n", *line);
		if (ret < 1)
			return (destroy_file(current_file, ret));
		if (!current_file->start)
			ret = update_line(current_file, line, size, ret);
		printf("-ret = %d\n", ret);
		//printf("-line = |%s|\n", *line);
		if (ret == -1)
			return (destroy_file(current_file, ret));
		current_file->start += ret - size - !(size);
		printf("-start    = %d\n", current_file->start);
		size = ret;
		current_file->start = current_file->start >= BUFFER_SIZE ? 0 : current_file->start;
		printf("--start   = %d\n", current_file->start);
		if ((*line)[size - 1] == '\n')
		{
			(*line)[size - 1] == 0;
			return (1);
		}
	}
}
