/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yarroubi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 17:59:05 by yarroubi          #+#    #+#             */
/*   Updated: 2021/08/16 15:47:56 by youness          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char				*b_ptr;
	char				*b_ptr2;
	unsigned long long	*qw_ptr;
	unsigned long long	*qw_ptr2;

	qw_ptr = (unsigned long long *)dst;
	qw_ptr2 = (unsigned long long *)src;
	while (n >= sizeof(unsigned long long))
	{
		*qw_ptr = *qw_ptr2;
		qw_ptr++;
		qw_ptr2++;
		n -= sizeof(unsigned long long);
	}
	b_ptr = (char *)qw_ptr;
	b_ptr2 = (char *)qw_ptr2;
	while (n--)
	{
		*b_ptr = *b_ptr2;
		b_ptr++;
		b_ptr2++;
	}
	return (dst);
}

void	ft_file_remove(t_file **files, int fd)
{
	t_file	*head;
	t_file	*next;
	t_file	*previous;

	head = *files;
	previous = 0;
	while (head)
	{
		next = head->next;
		if (head->fd == fd)
		{
			if (head == *files)
				*files = next;
			free(head);
			if (previous)
				previous->next = next;
			return ;
		}
		else
			previous = head;
		head = next;
	}
}

t_file	*ft_file_find(t_file *files, int fd)
{
	t_file	*tail;

	tail = files;
	while (tail)
	{
		if (tail->fd == fd)
			return (tail);
		tail = tail->next;
	}
	return (tail);
}

void	ft_file_addfront(t_file **files, t_file *node)
{
	if (node)
	{
		node->next = *files;
		*files = node;
	}
}

t_file	*ft_file_create(int fd)
{
	t_file	*file;

	file = malloc(sizeof(t_file));
	if (!file)
		return (0);
	file->fd = fd;
	file->start = 0;
	file->next = 0;
	return (file);
}
