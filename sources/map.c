/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:27:52 by ecastong          #+#    #+#             */
/*   Updated: 2024/04/12 18:17:38 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
t_list	*read_map(char *file_name)
{
	int		fd;
	t_list	*lines;
	char	*gnl_line;
	t_list	*new_line;

	fd = open(file_name, O_DIRECTORY);
	if (fd != -1)
		return (close(fd), ft_putendl_fd("Failed to open map.", ERR_FD), NULL);
	if (access(file_name, R_OK) == 0)
		fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (ft_putendl_fd("Failed to open map.", ERR_FD), NULL);
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
	lines = read_map(map_file);
	if (lines == NULL)
		return (NULL);
	map_x = 19;//
	map_y = 11;//
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
