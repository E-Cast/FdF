#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>
#include "MLX42/MLX42.h"
#define WIDTH 5120
#define HEIGHT 2880

unsigned int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

static void error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

int32_t	main(void)
{
	// Start mlx
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "Test", true);
	if (!mlx)
        error();

	// Create a new image
	mlx_image_t* img = mlx_new_image(mlx, 512, 512);
	if (!img)
		error();

	// Set every pixel to white
	memset(img->pixels, 255, img->width * img->height * sizeof(int32_t));
	// int get_rgba(int r, int g, int b, int a)
	unsigned int	i;
	unsigned int	j;
	i = 1;
	printf("%i\n", get_rgba(245, 40, 145, 0));
	while (i < img->height)
	{
		j = 1;
		while (j < img->width)
		{
			mlx_put_pixel(img, j, i, 0xF611FF);
			j++;
		}
		i++;
	}
	// Display an instance of the image
	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
        error();

	mlx_loop(mlx);

	// Optional, terminate will clean up any leftovers, this is just to demonstrate.
	mlx_delete_image(mlx, img);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
