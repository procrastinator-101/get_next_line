/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yarroubi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 17:13:02 by yarroubi          #+#    #+#             */
/*   Updated: 2021/03/27 22:00:43 by youness          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_file	*get_current_file(t_file **files, int fd)
{
	t_file	*tail;
	t_file	*current_file;

	tail = *files;
	while (tail)
	{
		if (tail->fd == fd)
			return (tail);
		if (tail->next)
			tail = tail->next;
		else
			break ;
	}
	current_file = malloc(sizeof(t_file));
	if (!current_file)
		return (0);
	current_file->fd = fd;
	current_file->start = 0;
	current_file->next = 0;
	if (tail)
		tail->next = current_file;
	else
		*files = current_file;
	return (current_file);
}

static int		destroy_file(t_file **files, int fd, int ret)
{
	t_file	*tail;

	tail = *files;
	while (tail)
	{
		if (tail->fd == fd)
		{
			free(tail);
			return (ret);
		}
		tail = tail->next;
	}
	return (ret);
}

int				get_next_line(int fd, char **line)
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
	while (1)
	{
		ret = 1;
		if (!current_file->start)
		{
			ret = read(current_file->fd, current_file->buffer, BUFFER_SIZE);
			if (ret > 0)
				current_file->buffer[ret] = 0;
		}
		if (ret < 1)
			return (destroy_file(&files, current_file->fd, ret));
		//printf("start = %d \t size = %d\n", current_file->start, size);
		size = update_line(current_file, line, size);
		//printf("start = %d \t size = %d\n", current_file->start, size);
		if (current_file->start >= BUFFER_SIZE)
			current_file->start = 0;
		if ((*line)[size - 1] == '\n')
		{
			(*line)[size - 1] = 0;
			return (1);
		}
	}
	return (1);
}
