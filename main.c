/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:45:29 by youness           #+#    #+#             */
/*   Updated: 2021/01/26 21:59:19 by youness          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

int main()
{
	char *line;

	int fd = open("get_next_line.h", O_RDONLY);
	//int fd = 0;
	int ret = 1;
	int i = 0;
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		printf("%s\n", line);
		free(line);
		i++;
	}
	printf("return = %d\n", ret);
	return (0);
}
