/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 18:45:12 by ecastong          #+#    #+#             */
/*   Updated: 2024/04/06 02:56:00 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <MLX42/MLX42.h>
# include "libft.h"

typedef struct s_dot
{
	int		x;
	int		y;
	int		z;
	int		color;
	void	*next;
}	t_dot;

typedef struct s_map
{
	int		height;
	int		width;
	t_dot	**dots;
}	t_map;

int		open_map(char *file_name);

t_dot	*make_new_dot(char *raw_data, int x, int y);

#endif