/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yarroubi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 17:59:05 by yarroubi          #+#    #+#             */
/*   Updated: 2021/01/26 19:37:31 by youness          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_strfcpy(char *dest, char *src, int size)
{
	long long	*holder;
	long long	*holder2;
	int			i;

	i = sizeof(long long);
	holder = (long long *)dest;
	holder2 = (long long *)src;
	while (i <= size)
	{
		*holder = *holder2;
		i += sizeof(long long);
		holder++;
		holder2++;
	}
	i -= sizeof(long long) + 1;
	while (++i < size)
		dest[i] = src[i];
}
