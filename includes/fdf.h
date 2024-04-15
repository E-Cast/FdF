/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 18:45:12 by ecastong          #+#    #+#             */
/*   Updated: 2024/04/15 17:27:25 by ecastong         ###   ########.fr       */
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
# include <MLX42/MLX42_Int.h>
# include "libft.h"

# ifndef XY_SCALE
#  define XY_SCALE 20
# endif

# ifndef Z_SCALE
#  define Z_SCALE 7
# endif

# ifndef DEFAULT_COLOR
#  define DEFAULT_COLOR 0xFFFFFFFF
# endif

# ifndef DEFAULT_ALPHA
#  define DEFAULT_ALPHA 0xFF
# endif


# ifndef DEFAULT_WIDTH
#  define DEFAULT_WIDTH 1280
# endif

# ifndef DEFAULT_HEIGHT
#  define DEFAULT_HEIGHT 720
# endif

# ifndef DEFAULT_ANGLE
#  define DEFAULT_ANGLE 0.523599
# endif

typedef struct s_dot
{
	int	x;
	int	y;
	int	z;
	int	color;
	int	sx;
	int	sy;
}	t_dot;

typedef struct s_modifiers
{
	int		xy_scale;
	int		z_scale;
	int		window_width;
	int		window_height;
	float	angle;
}	t_mods;

/*Map functions.*/

# ifndef O_DIRECTORY //test without it on mac.
#  define O_DIRECTORY	00200000
# endif

t_list	*read_map(char *map_file);
t_dot	*make_dot(char *raw_dot, int x, int y, size_t default_color);
t_dot	**line_to_dots(char *line, int y, size_t color);
t_dot	***build_map(char *map_file, size_t color);
void	free_map(t_dot	***map);

/*Line drawing functions.*/

void	low_slope(mlx_image_t *fdf, t_dot index, t_dot start, t_dot dest);
void	high_slope(mlx_image_t *fdf, t_dot index, t_dot start, t_dot dest);
void	draw_line(mlx_image_t *fdf, t_dot *start, t_dot *dest);
void	draw_all(mlx_image_t *fdf, t_dot ***map);

/*Color functions.*/

# ifndef GAMMA
#  define GAMMA 0.43
# endif

float	norm(int n);
float	intrp(float a, float b, float mix);
float	i_comp(float f);
int		comp(float f);
float	get_ratio(t_dot index, t_dot start, t_dot dest);
void	rgb_to_linear(int hex, float *rgba);
int		gradient(t_dot index, t_dot start, t_dot dest);






int		mlx_start(t_dot ***map, t_mods *mods);

#endif