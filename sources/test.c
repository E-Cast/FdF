/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:27:52 by ecastong          #+#    #+#             */
/*   Updated: 2024/04/04 02:58:46 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Opens the map file.
 * 
 * @param file_name Name of the file to be opened.
 * @retval Returns a valid fd on success.
 * @retval Returns -1 on failure.
 */
int	open_file(char *file_name)
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
