/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:27:52 by ecastong          #+#    #+#             */
/*   Updated: 2024/04/11 14:59:09 by ecastong         ###   ########.fr       */
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
int	open_map(char *file_name)
{
	int	fd;

	if (access(file_name, R_OK) == 0)
		fd = open(file_name, O_RDONLY);
	else
		fd = -1;
	if (fd == -1)
	{
		if (errno == ENOENT)
			ft_putstr_fd("File not found: ", STDERR_FILENO);
		else if (errno == EACCES)
			ft_putstr_fd("Permission denied: ", STDERR_FILENO);
		else
			ft_putstr_fd("Could not read data: ", STDERR_FILENO);
		ft_putendl_fd(file_name, STDERR_FILENO);
	}
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
 * @brief Creates an array of size x containing dots from the provided line.
 * 
 * @param line Str to extract the dots from.
 * @param map_x Size of the array to create.
 * @retval NULL On failure.
 * @retval On success an array of size x containing dots.
 */
t_dot	*line_to_dots(char *line, int map_x)
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
		if (line[inx] == ',')
		{
			map_line[map_inx].color = my_atoh(&line[inx + 1]);
		}
		else
			map_line[map_inx].color = DEFAULT_COLOR;
		while (line[inx] && my_isspace(line[inx]) == 0)
			inx++;
		while (line[inx] && my_isspace(line[inx]) != 0)
			inx++;
		map_inx++;
	}
	return (map_line);
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
		map_y--;
		map[map_y] = line_to_dots(ft_lstlast(lines)->content, map_x);
		if (map[map_y] == NULL)
			return (free_map(map, map_y + 1), ft_lstclear(&lines, free), NULL);
		my_lstdellast(&lines, free);
	}
	return (map);
}
