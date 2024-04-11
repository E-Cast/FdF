/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 02:58:48 by ecastong          #+#    #+#             */
/*   Updated: 2024/04/11 02:43:54 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Finds the number of dots in the line.
 * 
 * @param line Line containing the dots
 * @retval Number of dots in the line.
 */
static int	find_x(char *line)
{
	int	index;
	int	x;

	index = 0;
	x = 0;
	while (line[index] && my_isspace(line[index]) != 0)
		index++;
	while (line[index])
	{
		x++;
		while (line[index] && my_isspace(line[index]) == 0)
			index++;
		while (line[index] && my_isspace(line[index]) != 0)
			index++;
	}
	return (x);
}

/**
 * @brief Reads every line from the map and returns them in a linked list.
 * 
 * @param map_file File containing the map.
 * @param lines 
 * @param x Size x of the map.
 * @param y Size y of the map.
 * @retval NULL On failure.
 * @retval A pointer to the linked list containing every lines from the map.
 */
t_list	**read_map(char *map_file, t_list **lines, int *x, int *y)
{
	int		map_fd;
	char	*line;
	t_list	*new_line;

	map_fd = open_map(map_file);
	if (map_fd == -1)
		return (NULL);
	line = get_next_line(map_fd);
	while (line != NULL)
	{
		if (*x == 0)
			*x = find_x(line);
		else if (*x != find_x(line))
			return (ft_lstclear(lines, free), free(line), close(map_fd), NULL);
		(*y)++;
		new_line = ft_lstnew(line);
		if (new_line == NULL)
			return (ft_lstclear(lines, free), free(line), close(map_fd), NULL);
		ft_lstadd_back(lines, new_line);
		line = get_next_line(map_fd);
	}
	close(map_fd);
	return (lines);
}

/**
 * @brief Frees the map array and it's sub arrays.
 * 
 * @param map 3D array to be freed.
 * @param index Index to start freeing from.
 */
void	free_map(t_dot	**map, int index) //to move to another file
{
	while (map && map[index])
	{
		printf ("test 2\n");
		free(map[index++]);
	}
	printf ("test 3\n");
	free(map);
}

t_dot	*line_to_dots(char *line, int map_x)
{
	if (line && map_x > 12) ///
		return (ft_calloc(map_x + 1, sizeof(t_dot)));
	printf ("test 1\n");
	return (NULL);
}

/**
 * @brief Builds the map 3D array from the map file.
 * 
 * @param map_file Text file containing the map data.
 * @retval NULL on failure.
 * @retval The map on success.
 */
t_dot	**buil_map_arrays(char *map_file)
{
	int		map_x;
	int		map_y;
	t_list	*lines;
	t_dot	**map;

	map_x = 0;
	map_y = 0;
	lines = NULL;
	if (read_map(map_file, &lines, &map_x, &map_y) == NULL)
		return (ft_putendl_fd("Failed to read map.", STDERR_FILENO), NULL);
	map = ft_calloc(map_y + 1, sizeof(t_dot *));
	if (map == NULL)
		return (ft_lstclear(&lines, free), NULL);
	while (map_y > 0)
	{
		printf("y:%i\nx:%i\n\n", map_y, map_x--);
		map_y--;
		map[map_y] = line_to_dots(ft_lstlast(lines)->content, map_x);
		if (map[map_y] == NULL)
			return (free_map(map, map_y + 1), ft_lstclear(&lines, free), NULL);
		my_lstdellast(&lines, free);
	}
	return (map);
}

int	main(int argc, char **argv)
{
	t_dot	**map;

	map = buil_map_arrays(argv[1]);
	if (map == NULL)
		return (1);
	free_map(map, 0);
	(void) argc;
}

// int	main(int argc, char **argv)
// {
// 	int		map_fd;
// 	char	*line;
// 	int		str_index;
// 	int		x_index;
// 	int		y_index;

// 	map_fd = open(argv[1], O_RDONLY);
// 	if (map_fd == -1)
// 		return (1);
// 	y_index = 1;
// 	line = get_next_line(map_fd);
// 	while (line != NULL)
// 	{
// 		printf("Line %i\n", y_index);
// 		str_index = 0;
// 		x_index = 1;
// 		if (my_isspace(line[str_index]))
// 			str_index++;
// 		while (line[str_index] != '\0')
// 		{
// 			if (my_isspace(line[str_index]) == 0)
// 			{
// 				printf("x:%i\ny:%i\nz:%i\n",
// 					x_index, y_index, ft_atoi(&line[str_index]));
// 				while (line[str_index] && (my_isspace(line[str_index]) == 0 && line[str_index] != ','))
// 					str_index++;
// 				if (line[str_index] == ',')
// 					printf("color:0x%lx\n", my_atoh(&line[str_index + 1]));
// 				while (line[str_index] && my_isspace(line[str_index]) == 0)
// 					str_index++;
// 				printf("\n");
// 				x_index++;
// 			}
// 			else
// 				while (line[str_index] && my_isspace(line[str_index]))
// 					str_index++;
// 		}
// 		y_index++;
// 		free(line);
// 		line = get_next_line(map_fd);
// 	}
// 	(void) argc;
// 	return (0);
// }

// t_dot	*new_dot(char *dot_data, int x, int y)
// {
// 	t_dot	*dot;

// 	dot = malloc(sizeof(t_dot));
// 	if (!dot)
// 		return (NULL);
// 	dot->x = x;
// 	dot->y = y;
// 	dot->z = ft_atoi(dot_data);
// 	if (ft_strchr(dot_data, ','))
// 		dot->color = my_atoh(ft_strchr(dot_data, ',') + 1);
// 	dot->next = NULL;
// 	return (dot);
// }

// t_dot	*line_to_dots(t_dot	**dots, char *line, int map_width, int map_height)
// {
// 	char	**split_line;
// 	int		index;


// 	split_line = ft_split(line, ' ');
// 	if (split_line == NULL)
// 		return (NULL); // free dots and line then return
// 	while (split_line[index])
// 	{
		
// 		index++;
// 	}
// }

// t_dot	*make_dots_list(char *filename, int map_width, int map_height)
// {
// 	int		map_file;
// 	char	*line;
// 	t_dot	*dots;

// 	map_file = open_map(filename);
// 	if (map_file == -1)
// 		return (NULL);
// 	line = get_next_line(map_file);
// 	while (line != NULL)
// 	{
// 		map_height++;
// 		dots = line_to_dots(&dots, line, map_width, &map_height);
// 		free (line);
// 		if (dots == NULL)
// 			return (NULL);
// 		line = get_next_line(map_file);
// 	}
// }

// int	main(int argc, char **argv)
// {
// 	int		map_width;
// 	int		map_height;
// 	t_dot	*dots;

// 	if (argc < 2 || argc > 4)
// 	{
// 		ft_putendl_fd("Args:\n<filename> [length] [height]", STDERR_FILENO);
// 		return (EXIT_FAILURE);
// 	}
// 	map_width = -1;
// 	map_height = 0;
// 	dots = make_dots_list(argv[1], &map_width, &map_height);
// 	(void) argv;
// 	dots = new_dot("-9,0xff", 4, 2);
// 	printf("x:%i\ny:%i\nz:%i\ncolor:%lx\n", dots->x, dots->y, dots->z, dots->color);
// }
