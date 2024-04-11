/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 18:45:12 by ecastong          #+#    #+#             */
/*   Updated: 2024/04/10 20:55:16 by ecastong         ###   ########.fr       */
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
	int		x;
	int		y;
	int		z;
	size_t	color;
	void	*cntd_x;
	void	*cntd_y;
	void	*next_dot;
}	t_dot;

int		open_map(char *file_name);

t_dot	*make_new_dot(char *raw_data, int x, int y);

#endif