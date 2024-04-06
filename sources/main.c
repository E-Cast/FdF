/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 02:58:48 by ecastong          #+#    #+#             */
/*   Updated: 2024/04/06 02:31:35 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_dot	*dot;
	// mlx_t	*mlx;

	// mlx = mlx_init(500, 500, "window", 1);
	// mlx_loop(mlx);
	// mlx_terminate(mlx);
	// printf("%i\n", open_map(argv[1]));
	// mlx_init(10, 10, "test", 0);
	dot = make_new_dot("9,0xff", 2, 1);
	printf("X:%i\nY:%i\nZ:%i\nColor:%i\n", dot->x, dot->y, dot->z, dot->color);
	(void) argc;
	(void) argv;
}
