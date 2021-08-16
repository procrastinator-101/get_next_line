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

int	update_line(t_file *file, char **line, int size)
{
	int		i;
    int		new_size;
    char    *str;

	i = file->start;
    while (file->buffer[i] && file->buffer[i] != '\n')
        i++;
	if (size)
		size--;
	new_size = size + i + 1 - file->start;
    str = malloc(new_size * sizeof(char));
    if (!str)
    {
        free(*line);
        *line = 0;
        return (-1);
    }
    ft_memcpy(str, *line, size);
    ft_memcpy(str + size, file->buffer + file->start, new_size - size);
	if (!file->buffer[i] || !file->buffer[i + 1])
		file->start = 0;
	else
		file->start += new_size - size;
    free(*line);
    *line = str;
    return (new_size);
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
		if (!current_file->start)
		{
			ret = read(current_file->fd, current_file->buffer, BUFFER_SIZE);
			if (ret > 0)
				current_file->buffer[ret] = 0;
			else
			{
				ft_file_remove(&files, current_file->fd);
				return (ret);
			}
		}
		//printf("start = %d \t size = %d last = %d\n", current_file->start, size, current_file->buffer[current_file->start]);
		size = update_line(current_file, line, size);
		if (current_file->start >= BUFFER_SIZE)
			current_file->start = 0;
		//printf("++start = %d \t size = %d last = %d\n", current_file->start, size, current_file->buffer[current_file->start]);
		if ((*line)[size - 1] == '\n')
		{
			(*line)[size - 1] = 0;
			return (1);
		}
	}
	return (1);
}
