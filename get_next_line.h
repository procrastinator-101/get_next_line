/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yarroubi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 17:11:01 by yarroubi          #+#    #+#             */
/*   Updated: 2021/03/27 21:19:22 by youness          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# define RET_SUCCESS	-2

typedef struct s_file
{
	int				fd;
	int				start;
	char			buffer[BUFFER_SIZE + 1];
	struct s_file	*next;
}					t_file;

int					get_next_line(int fd, char **line);
void				*ft_memcpy(void *dst, const void *src, size_t n);

t_file				*ft_file_create(int fd);
t_file				*ft_file_find(t_file *files, int fd);

void				ft_file_remove(t_file **files, int fd);
void				ft_file_addfront(t_file **files, t_file *node);

#endif
