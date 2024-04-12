/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 18:45:12 by ecastong          #+#    #+#             */
/*   Updated: 2024/04/11 23:23:07 by ecastong         ###   ########.fr       */
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

# ifndef XY_SCALE
#  define XY_SCALE 10
# endif

# ifndef Z_SCALE
#  define Z_SCALE 10
# endif

# ifndef DEF_COLOR
#  define DEF_COLOR 0xFFFFFFFF
# endif

typedef struct s_data
{
	int		xy_scale;
	int		z_scale;
	size_t	def_color;
	int		max_x;
	int		max_y;
	float	angle;
}	t_data;

typedef struct s_dot
{
	int		z;
	size_t	color;
	bool	last;
}	t_dot;

// map.c

int		open_map(char *file_name);
t_list	**read_map(char *map_file, t_list **lines, int *x, int *y);
t_dot	*line_to_dots(char *line, int map_x, size_t	color);
t_dot	**buil_map_arrays(char *map_file, t_data *data);

// util.c

int		find_x(char *line);
int		fdf_atoi(const char *str, int *index);
void	free_map(t_dot	**map, int index);

t_dot	*make_new_dot(char *raw_data, int x, int y);
#endif