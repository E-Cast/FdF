/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 02:58:48 by ecastong          #+#    #+#             */
/*   Updated: 2024/04/04 02:59:22 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	// mlx_t	*mlx;

	// mlx = mlx_init(500, 500, "window", 1);
	// mlx_loop(mlx);
	// mlx_terminate(mlx);
	printf("%i\n", open_file(argv[1]));
	mlx_init(10, 10, "test", 0);
	(void) argc;
}
