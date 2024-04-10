/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 18:45:12 by ecastong          #+#    #+#             */
/*   Updated: 2024/04/09 22:38:31 by ecastong         ###   ########.fr       */
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
	size_t	color;
	void	*next;
}	t_dot;

int		open_map(char *file_name);

t_dot	*make_new_dot(char *raw_data, int x, int y);

#endif