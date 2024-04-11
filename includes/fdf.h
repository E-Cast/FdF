/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 18:45:12 by ecastong          #+#    #+#             */
/*   Updated: 2024/04/11 14:54:18 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <MLX42/MLX42.h>
# include "libft.h"

# ifndef DEFAULT_COLOR
#  define DEFAULT_COLOR 0xFFFFFFFF
# endif

# ifndef X_Y_SCALE
#  define X_Y_SCALE 10
# endif

# ifndef Z_SCALE
#  define Z_SCALE 10
# endif

typedef struct s_dot
{
	int		z;
	size_t	color;
}	t_dot;

// map.c

int		open_map(char *file_name);
t_list	**read_map(char *map_file, t_list **lines, int *x, int *y);
t_dot	*line_to_dots(char *line, int map_x);
t_dot	**buil_map_arrays(char *map_file);

// util.c

int		find_x(char *line);
int		fdf_atoi(const char *str, int *index);
void	free_map(t_dot	**map, int index);

t_dot	*make_new_dot(char *raw_data, int x, int y);
#endif