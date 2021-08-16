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

int main(int argc, char **argv)
{
	int		ret;
	int		fd[argc - 1];
	char	*line;

	if (argc < 2)
		return (0);
	for (int i = 0; i < argc - 1; i++)
		fd[i] = open(argv[i + 1], O_RDONLY);
	for (int i = 0; i < argc - 1; i++)
	{
		while (1)
		{
			ret = get_next_line(fd[i], &line);
			if (ret < 1)
				break ;
			printf("%s\n", line);
			free(line);
			//printf("ret = %d\n", ret);
		}
		//printf("return = %d\n", ret);
	}
	return (0);
}
