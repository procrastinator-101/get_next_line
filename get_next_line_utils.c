/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yarroubi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 17:59:05 by yarroubi          #+#    #+#             */
/*   Updated: 2021/01/25 18:24:21 by yarroubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_strcncpy(char *dest, char *src, char c, int len)
{
	int	i;

	i = -1;
	while (++i < len && src[i] != c)
		dest[i] = src[i];
	if (len > 0)
		dest[len - 1] = 0;
}
