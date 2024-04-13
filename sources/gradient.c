/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 19:10:00 by ecastong          #+#    #+#             */
/*   Updated: 2024/04/13 19:25:23 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// /**
//  * @brief Calculates where x is in between x1 and x2.
//  * 
//  * @param x1 Start position.
//  * @param x2 Destination position.
//  * @param x Current position.
//  * @retval A float ranging from 0.000 to 1.000, 
//  * 0 being x at x1 and 1 being x at x2.
//  */
// float	get_progress(float x1, float x2, float x)
// {
// 	if (x1 != x2)
// 		return ((x - x1) / (x2 - x1));
// 	return (0);
// }

// size_t	gradient(t_dot index, t_dot strt, t_dot dest)
// {
// 	int		dx;
// 	int		dy;
// 	float	fraction;
// 	int		rgba[4];

// 	dx = dest.x - strt.sx;//
// 	dy = dest.y - strt.sy;
// 	if (abs(dx) > abs(dy))
// 		fraction = get_progress(strt.sx, dest.sx, index.sx);
// 	else
// 		fraction = get_progress(strt.sy, dest.sy, index.sy);
// 	rgba[0] = (strt.color >> 24 & 0xFF) + ((dest.color >> 24 & 0xFF)
// 			- (strt.color >> 24 & 0xFF)) * fraction;
// 	rgba[1] = (strt.color >> 16 & 0xFF) + ((dest.color >> 16 & 0xFF)
// 			- (strt.color >> 16 & 0xFF)) * fraction;
// 	rgba[2] = (strt.color >> 8 & 0xFF) + ((dest.color >> 8 & 0xFF)
// 			- (strt.color >> 8 & 0xFF)) * fraction;
// 	rgba[3] = (strt.color & 0xFF) + ((dest.color & 0xFF)
// 			- (strt.color & 0xFF)) * fraction;
// 	printf("fraction%f\n", fraction);
// 	return (rgba[0] << 24 | rgba[1] << 16 | rgba[2] << 8 | rgba[3]);
// }

/**
 * @brief Calculates how far index is between start 
 * and end and how to mix the colors accordingly.
 * 
 * @param start Start position.
 * @param end Destination position.
 * @param indexx Current position.
 * @retval A float ranging from 0.000 to 1.000, 
 * 0 being x at x1 and 1 being x at x2.
 */
float	get_mix(t_dot index, t_dot start, t_dot dest)
{
	int		dx;
	int		dy;
	float	mix;

	dx = dest.x - start.sx;
	dy = dest.y - start.sy;
	mix = 0;
	if (abs(dx) > abs(dy))
	{
		if (start.sx != dest.sx)
			mix = ((float)index.sx - (float)start.sx)
				/ ((float)dest.sx - (float)start.sx);
	}
	else
	{
		if (start.sy != dest.sy)
			mix = ((float)index.sy - (float)start.sy)
				/ ((float)dest.sy - (float)start.sy);
	}
	return (mix);
}

size_t	gradient(t_dot index, t_dot strt, t_dot dest)
{
	float	fraction;
	int		rgba[4];

	fraction = get_mix(index, strt, dest);
	rgba[0] = (strt.color >> 24 & 0xFF) + ((dest.color >> 24 & 0xFF)
			- (strt.color >> 24 & 0xFF)) * fraction;
	rgba[1] = (strt.color >> 16 & 0xFF) + ((dest.color >> 16 & 0xFF)
			- (strt.color >> 16 & 0xFF)) * fraction;
	rgba[2] = (strt.color >> 8 & 0xFF) + ((dest.color >> 8 & 0xFF)
			- (strt.color >> 8 & 0xFF)) * fraction;
	rgba[3] = (strt.color & 0xFF) + ((dest.color & 0xFF)
			- (strt.color & 0xFF)) * fraction;
	printf("fraction%f\n", fraction);
	return (rgba[0] << 24 | rgba[1] << 16 | rgba[2] << 8 | rgba[3]);
}
