/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 20:35:54 by ecastong          #+#    #+#             */
/*   Updated: 2024/04/10 22:58:12 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_dot	*line_to_dots(t_dot **dots, char *line, int y)
{
	t_dot	*new_dot;
	int		x;
	int		line_indx;

	x = 1;
	line_indx = 0;
	while (line[line_indx])
	{
		line_indx++;
	}
	if (*dots == NULL)
		*dots = new_dot;
	else
		dot_add_back(dots, new_dot);
}

// int	main(int argc, char **argv)
// {
// 	int		map_fd;
// 	t_dot	*dots;
// 	char	*line;
// 	int		y;

// 	map_fd = open(argv[1], O_RDONLY);
// 	if (map_fd == -1)
// 		return (1);
// 	dots = NULL;
// 	line = get_next_line(map_fd);
// 	y = 1;
// 	while (line != NULL)
// 	{
// 		dots = line_to_dots(&dots, line, y);
// 		y++;
// 		free(line);
// 		line = get_next_line(map_fd);
// 	}
// 	while (dots != NULL)
// 	{
// 		printf("x:%i\ny:%i\nz:%i\ncolor:%lx\ncntd_x:%p\ncntd_y:%p\n\n",
// 			dots->x, dots->y, dots->z, dots->color, dots->cntd_x, dots->cntd_y);
// 		dots = dots->next_dot;
// 	}
// }
