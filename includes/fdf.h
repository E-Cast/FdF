/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 18:45:12 by ecastong          #+#    #+#             */
/*   Updated: 2024/04/12 04:07:55 by ecastong         ###   ########.fr       */
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
#  define XY_SCALE 20
# endif

# ifndef Z_SCALE
#  define Z_SCALE 7
# endif

# ifndef DEF_COLOR
#  define DEF_COLOR 0xFFFFFFFF
# endif

# ifndef DEF_ANGLE
#  define DEF_ANGLE 0.523599
# endif

typedef struct s_data
{
	ssize_t	xy_scale;
	ssize_t	z_scale;
	ssize_t	def_color;
	ssize_t	max_x;
	ssize_t	max_y;
	ssize_t	max_z;
	float	angle;
}	t_data;

typedef struct s_dot
{
	ssize_t	x;
	ssize_t	y;
	ssize_t	z;
	ssize_t	color;
	bool	last;
}	t_dot;

// map.c

int		open_map(char *file_name);
t_list	**read_map(char *map_file, t_list **lines, int *x, int *y);
t_dot	*line_to_dots(char *line, int map_x, t_data *data);
t_dot	**buil_map_arrays(char *map_file, t_data *data);

// util.c

int		find_x(char *line);
int		fdf_atoi(const char *str, int *index);
void	free_map(t_dot	**map, int index);

t_dot	*make_new_dot(char *raw_data, int x, int y);
#endif