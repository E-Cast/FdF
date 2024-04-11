/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 02:58:48 by ecastong          #+#    #+#             */
/*   Updated: 2024/04/10 23:53:26 by ecastong         ###   ########.fr       */
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
	char	*read_line;
	t_list	*new_line;

	map_fd = open(map_file, O_RDONLY);
	if (map_fd == -1)
		return (NULL);
	read_line = get_next_line(map_fd);
	while (read_line != NULL)
	{
		if (*x == -1)
			*x = find_x(read_line);
		else if (*x != find_x(read_line))
			return (ft_lstclear(lines, free), free(read_line), NULL);
		(*y)++;
		new_line = ft_lstnew(read_line);
		if (new_line == NULL)
			return (ft_lstclear(lines, free), free(read_line), NULL);
		ft_lstadd_back(lines, new_line);
		read_line = get_next_line(map_fd);
	}
	return (lines);
}

int	main(int argc, char **argv)
{
	int		x;
	int		y;
	t_list	*lines;
	t_list	*lines_index;

	x = -1;
	y = 0;
	lines = NULL;
	if (read_map(argv[1], &lines, &x, &y) == NULL)
	{
		ft_putendl_fd("Error: Failed to read map.", STDERR_FILENO);
		return (1);
	}

	lines_index = lines;
	printf("x:%i\ny:%i\n", x, y);
	while (lines_index != NULL)
	{
		printf("%s\n", (char *)lines_index->content);
		lines_index = lines_index->next;
	}
	ft_lstclear(&lines, free);
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
