/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:27:52 by ecastong          #+#    #+#             */
/*   Updated: 2024/04/06 03:33:21 by ecastong         ###   ########.fr       */
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
			ft_putstr_fd("Invalid filename: ", STDERR_FILENO);
		ft_putendl_fd(file_name, STDERR_FILENO);
	}
	return (fd);
}

t_dot	*make_new_dot(char *raw_data, int x, int y)
{
	t_dot	*dot;
	char	**data;

	dot = ft_calloc(1, sizeof(t_dot));
	if (dot == NULL)
		return (NULL);
	dot->x = x;
	dot->y = y;
	dot->next = NULL;
	if (ft_strchr(raw_data, ',') == NULL)
	{
		dot->z = ft_atoi(raw_data);
		dot->color = 255; //default color placeholder, should maybe do a define
		return (dot);
	}
	data = ft_split(raw_data, ',');
	if (data == NULL)
		return (my_safefree(dot));
	dot->z = ft_atoi(data[0]);
	dot->color = ft_hex(data[1]);
	return (dot);
}

// t_map	read_map(int map_fd)
// {
// 	t_map	map;
// 	t_dot	dots[100];
// 	char	*line;
// 	int		index;

// 	map.height = 0;
// 	line = get_next_line(map_fd);
// 	while (line != NULL)
// 	{

// 		line = get_next_line(map_fd);
// 	}
// }
