/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yarroubi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 17:13:02 by yarroubi          #+#    #+#             */
/*   Updated: 2021/01/26 21:48:11 by youness          ###   ########.fr       */
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
	//hard free
	if (!current_file)
		return (0);
	current_file->fd = fd;
	current_file->start = 0;
	current_file->next = 0;
	current_file->previous = tail;
	if (tail)
		tail->next = current_file;
	else
		*files = current_file;
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
	current_file = get_current_file(&files, fd);
	if (!current_file)
		return (-1);
	while (1)
	{
		printf("first_start = %d\n", current_file->start);
		if (current_file->start)
			ret =  update_line(current_file, line, size, BUFFER_SIZE - current_file->start);
		else
			ret = read(current_file->fd, current_file->buffer, BUFFER_SIZE);
		//free line
		if (ret < 1)
			return (destroy_file(current_file, ret));
		if (!current_file->start)
			ret = update_line(current_file, line, size, ret);
		//free line
		if (ret == -1)
			return (destroy_file(current_file, ret));
		current_file->start += ret - size;
		printf("start = %d\n", current_file->start);
		printf("ret   = %d\n", ret);
		printf("size  = %d\n", size);
		size = ret;
		current_file->start = current_file->start >= BUFFER_SIZE ? 0 : current_file->start;
		printf("new_start = %d\n", current_file->start);
		if ((*line)[size - 1] == '\n')
		{
			(*line)[size - 1] = 0;
			return (1);
		}
	}
	return (1);
}
