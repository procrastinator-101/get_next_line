/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 20:38:34 by youness           #+#    #+#             */
/*   Updated: 2021/01/26 21:32:56 by youness          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int      update_line(t_file *file, char **line, int dst_len, \
                int src_len)
{
    int     size;
    char    *str;

    size = 1;
    while (size - 1 < src_len && file->buffer[file->start + size - 1] != '\n')
        size++;
	size = size <= src_len ? size : src_len;
    str = malloc((dst_len + size) * sizeof(char));
    if (!str)
    {
        free(*line);
        *line = 0;
        return (-1);
    }
    ft_strfcpy(str, *line, dst_len);
    ft_strfcpy(str + dst_len, file->buffer + file->start, size);
    free(*line);
    *line = str;
    return (dst_len + size);
}

