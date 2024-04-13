/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:27:52 by ecastong          #+#    #+#             */
/*   Updated: 2024/04/12 21:55:55 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Reads every line from the map file and returns them in a linked list.
 * 
 * @param file_name Name of the file to read from.
 * @retval NULL On failure.
 * @retval A linked list containing every line from the file on success.
 */
t_list	*read_map(char *file_name)
{
	int		fd;
	t_list	*lines;
	char	*gnl_line;
	t_list	*new_line;

	fd = open(file_name, O_DIRECTORY);
	if (fd != -1)
		return (NULL);
	if (access(file_name, R_OK) == 0)
		fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (NULL);
	lines = NULL;
	gnl_line = get_next_line(fd);
	while (gnl_line)
	{
		new_line = ft_lstnew(gnl_line);
		if (new_line == NULL)
			return (ft_lstclear(&lines, free), free(gnl_line), close(fd), NULL);
		ft_lstadd_back(&lines, new_line);
		gnl_line = get_next_line(fd);
	}
	return (close(fd), lines);
}

/**
 * @brief Allocates, fills and returns a dot struct.
 * 
 * @param raw_dot Raw data used to fill the struct.
 * @param x Data used to fill the struct.
 * @param y Data used to fill the struct.
 * @param default_color Data used to fill the struct.
 * @retval NULL On failure.
 * @retval A dot struct on success.
 */
t_dot	*make_dot(char *raw_dot, int x, int y, size_t default_color)
{
	t_dot	*new_dot;

	new_dot = ft_calloc(1, sizeof(t_dot));
	if (new_dot == NULL)
		return (NULL);
	new_dot->x = x;
	new_dot->y = y;
	new_dot->z = ft_atoi(raw_dot);
	while (*raw_dot && my_isspace(*raw_dot) != 0)
		raw_dot++;
	while (*raw_dot && (my_isspace(*raw_dot) == 0 && *raw_dot != ','))
		raw_dot++;
	if (*raw_dot == ',')
		new_dot->color = my_atoh(raw_dot + 1);
	else
		new_dot->color = default_color;
	return (new_dot);
}

/**
 * @brief Extracts every dots from line into an array.
 * 
 * @param line Str to extract the dots from.
 * @param y Data to fill the dots with.
 * @param color Data to fill the dots with.
 * @retval NULL On failure.
 * @retval An array of dots on success.
 */
t_dot	**line_to_dots(char *line, int y, size_t color)
{
	t_dot	**map_line;
	int		inx;
	int		map_x;

	inx = 0;
	map_x = 0;
	if (line[0] && !my_isspace(line[0]))
		map_x = 1;
	while (line[inx++])
		if (line[inx] && my_isspace(line[inx - 1]) && !my_isspace(line[inx]))
			map_x++;
	map_line = ft_calloc(map_x + 1, sizeof(t_dot *));
	inx = 0;
	while (map_line && *line && inx < map_x)
	{
		map_line[inx] = make_dot(line, inx + 1, y, color);
		if (map_line[inx] == NULL)
			return (my_freearr((void **)map_line, inx), NULL);
		inx++;
		while (my_isspace(*line) != 0)
			line++;
		while (*line && my_isspace(*line) == 0)
			line++;
	}
	return (map_line);
}

/**
 * @brief Builds the 3D array map from the map file.
 * 
 * @param map_file Text file containing the map data.
 * @param color Default color for dots.
 * @retval NULL on failure.
 * @retval The map on success.
 */
t_dot	***build_map(char *map_file, size_t color)
{
	t_list	*lines;
	t_list	*line_indx;
	t_dot	***map;
	int		map_indx;
	int		map_x;

	lines = read_map(map_file);
	if (lines == NULL)
		return (NULL);
	line_indx = lines;
	map = ft_calloc(ft_lstsize(lines) + 1, sizeof(t_dot *));
	map_indx = 0;
	while (map && line_indx)
	{
		map[map_indx] = line_to_dots(line_indx->content, map_indx + 1, color);
		if (map[map_indx++] == NULL)
			return (free_map(map), ft_lstclear(&lines, free), NULL);
		map_x = 0;
		while (map[0][map_x] && map[map_indx - 1][map_x])
			map_x++;
		if (map[0][map_x] || map[map_indx - 1][map_x])
			return (free_map(map), ft_lstclear(&lines, free), NULL);
		line_indx = line_indx->next;
	}
	return (ft_lstclear(&lines, free), map);
}

/**
 * @brief Frees the map array and it's sub arrays.
 * 
 * @param map 3D array to be freed.
 * @param index Index to start freeing from.
 */
void	free_map(t_dot	***map)
{
	int	y_indx;
	int	x_indx;

	if (!map)
		return ;
	y_indx = 0;
	while (map && map[y_indx])
	{
		x_indx = 0;
		while (map[y_indx][x_indx])
			my_safefree(map[y_indx][x_indx++]);
		my_safefree(map[y_indx++]);
	}
	my_safefree(map);
}
