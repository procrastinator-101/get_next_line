/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yarroubi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 17:11:01 by yarroubi          #+#    #+#             */
/*   Updated: 2021/01/26 19:14:16 by youness          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct		s_file
{
	int				fd;
	int				start;
	char			buffer[BUFFER_SIZE];
	struct s_file	*next;
	struct s_file	*previous;
}					t_file;

int					get_next_line(int fd, char **line);
void				ft_strfcpy(char *dest, char *src, int size);

#endif
