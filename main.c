/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:45:29 by youness           #+#    #+#             */
/*   Updated: 2021/03/27 22:03:42 by youness          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

int main()
{
	char *line;

	int fd1 = open("get_next_line.h", O_RDONLY);
	int fd2 = open("input", O_RDONLY);
	int fd3 = open("get_next_line.c", O_RDONLY);
	int fd = fd1;
	int ret = 1;
	int i = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		printf("%s\n", line);
		free(line);
		i++;
		if (i % 2)
			fd = fd2;
		else
			fd = fd3;
	}
	printf("return = %d\n", ret);
	return (0);
}
