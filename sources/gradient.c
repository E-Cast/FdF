/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 19:10:00 by ecastong          #+#    #+#             */
/*   Updated: 2024/04/14 00:12:42 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
float	get_ratio(t_dot index, t_dot start, t_dot dest)
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

void	prep_color(int *rgb, float *res)
{
	res[0] = i_comp(norm(rgb[0]));
	res[1] = i_comp(norm(rgb[1]));
	res[2] = i_comp(norm(rgb[2]));
}

// Main MarkMix function
int	mark_mix(int *rgb1, int *rgb2, float mix)
{
	float	tmp1[3];
	float	tmp2[3];
	float	rgba[4];
	float	brightness;
	float	factor;

	prep_color(rgb1, tmp1);
	prep_color(rgb2, tmp2);
	rgba[0] = intrp(tmp1[0], tmp2[0], mix);
	rgba[1] = intrp(tmp1[1], tmp2[1], mix);
	rgba[2] = intrp(tmp1[2], tmp2[2], mix);
	brightness = intrp(pow(tmp1[0] + tmp1[1] + tmp1[2], GAMMA),
			pow(tmp2[0] + tmp2[1] + tmp2[2], GAMMA), mix);
	if ((rgba[0] + rgba[1] + rgba[2]) != 0)
	{
		factor = pow(brightness, 1 / GAMMA) / (rgba[0] + rgba[1] + rgba[2]);
		rgba[0] *= factor;
		rgba[1] *= factor;
		rgba[2] *= factor;
	}
	rgba[3] = rgb1[3] + (rgb2[3] - rgb1[3]) * mix;
	return (comp(rgba[0]) << 24 | comp(rgba[1]) << 16
		| comp(rgba[2]) << 8 | (int)rgba[3]);
}

void	hex_to_rgba(int hex, int *rgba)
{
	rgba[0] = ((hex >> 24) & 0xFF);
	rgba[1] = ((hex >> 16) & 0xFF);
	rgba[2] = ((hex >> 8) & 0xFF);
	rgba[3] = (hex & 0xFF);
}

int	gradient(t_dot index, t_dot start, t_dot dest)
{
	int		rgba1[4];
	int		rgba2[4];
	float	mix;

	hex_to_rgba(start.color, rgba1);
	hex_to_rgba(dest.color, rgba2);
	mix = get_ratio(index, start, dest);
	return (mark_mix(rgba1, rgba2, mix));
}
