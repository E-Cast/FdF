/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:27:52 by ecastong          #+#    #+#             */
/*   Updated: 2024/04/12 17:52:21 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Opens the file containing the map.
 * 
 * @param file_name Name of the file to be opened.
 * @retval Returns a valid fd on success.
 * @retval Returns -1 on failure.
 */
int	open_map_file(char *file_name)
{
	int	fd;

	fd = open(file_name, O_DIRECTORY);
	if (fd != -1)
		return (close(fd), ft_putendl_fd("Failed to open map.", ERR_FD), -1);
	if (access(file_name, R_OK) == 0)
		fd = open(file_name, O_RDONLY);
	if (fd == -1)
		ft_putendl_fd("Failed to open map.", ERR_FD);
	return (fd);
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

	map_fd = open_map_file(map_file);
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
 * @brief Creates an array of size x containing dots from the provided line.
 * 
 * @param line Str to extract the dots from.
 * @param map_x Size of the array to create.
 * @param data General fdf data.
 * @retval NULL On failure.
 * @retval On success an array of size x containing dots.
 */
t_dot	*line_to_dots(char *line, int map_x, t_data *data)
{
	t_dot	*map_line;
	int		map_inx;
	int		inx;

	map_line = ft_calloc(map_x + 1, sizeof(t_dot));
	if (map_line == NULL)
		return (NULL);
	inx = 0;
	map_inx = 0;
	while (line[inx] && map_inx < map_x)
	{
		map_line[map_inx].z = fdf_atoi(line, &inx);
		if (map_line[map_inx].z > data->max_z)
			data->max_z = map_line[map_inx].z;
		if (line[inx] == ',')
			map_line[map_inx].color = my_atoh(&line[inx + 1]);
		else
			map_line[map_inx].color = data->def_color;
		while (line[inx] && my_isspace(line[inx]) == 0)
			inx++;
		while (line[inx] && my_isspace(line[inx]) != 0)
			inx++;
		map_inx++;
	}
	return (map_line);
}

/**
 * @brief 
 * 
 * @param map 
 * @param data 
 */
void	index_map(t_dot **map, t_data *data)
{
	ssize_t	y;
	ssize_t	x;

	y = 0;
	while (y < data->max_y)
	{
		x = 0;
		while (x < data->max_x)//
		{
			map[y][x].x = x + 1;
			map[y][x].y = y + 1;
			x++;
		}
		y++;
	}
}

/**
 * @brief Builds the map 3D array from the map file.
 * 
 * @param map_file Text file containing the map data and settings.
 * @param data General fdf data.
 * @retval NULL on failure.
 * @retval The map on success.
 */
t_dot	**build_map_arrays(char *map_file, t_data *data)
{
	int		map_x;
	int		map_y;
	t_list	*lines;
	t_dot	**map;

	map_x = 0;
	map_y = 0;
	lines = NULL;
	if (read_map(map_file, &lines, &map_x, &map_y) == NULL)
		return (NULL);
	data->max_x = map_x;
	data->max_y = map_y;
	map = ft_calloc(map_y + 1, sizeof(t_dot *));
	if (map == NULL)
		return (ft_lstclear(&lines, free), NULL);
	while (map_y > 0)
	{
		map_y--;
		map[map_y] = line_to_dots(ft_lstlast(lines)->content, map_x, data);
		if (map[map_y] == NULL)
			return (free_map(map, map_y + 1), ft_lstclear(&lines, free), NULL);
		my_lstdellast(&lines, free);
	}
	return (index_map(map, data), map);
}
