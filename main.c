/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c 		                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaetern <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 02:58:20 by ksaetern          #+#    #+#             */
/*   Updated: 2017/03/24 02:58:24 by ksaetern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

int		main(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (argc < 2)
		return (0);
	fd = open(argv[1], O_RDONLY);
	while (get_next_line(fd, &line) == 1)
	{
		ft_putendl(line);
		free(line);
	}
	close(fd);
	return (0);
}
