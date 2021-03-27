/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 20:38:34 by youness           #+#    #+#             */
/*   Updated: 2021/03/27 22:00:10 by youness          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
    ft_strfcpy(str, *line, size);
    ft_strfcpy(str + size, file->buffer + file->start, new_size - size);
	if (file->buffer[i])
		file->start += new_size - size;
	else
		file->start = 0;
    free(*line);
    *line = str;
    return (new_size);
}

