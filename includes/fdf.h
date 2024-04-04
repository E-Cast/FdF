/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 18:45:12 by ecastong          #+#    #+#             */
/*   Updated: 2024/04/04 02:59:49 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <MLX42/MLX42.h>
# include "libft.h"

int	open_file(char *file_name);

#endif