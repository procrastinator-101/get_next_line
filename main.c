/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:45:29 by youness           #+#    #+#             */
/*   Updated: 2021/01/26 20:25:34 by youness          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

int main()
{
	char *line;

	int fd = open("get_next_line.h", O_RDONLY);
	int ret = 1;
	int i = 0;
	while (ret > 0 && i < 2)
	{
		ret = get_next_line(fd, &line);
		printf("%s", line);
		free(line);
		i++;
	}
	return (0);
}
