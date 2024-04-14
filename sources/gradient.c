/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 19:10:00 by ecastong          #+#    #+#             */
/*   Updated: 2024/04/14 00:32:54 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Calculates how far index is between start and end.
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

void	hex_to_rgba(int hex, float *rgba)
{
	rgba[0] = i_comp(norm(((hex >> 24) & 0xFF)));
	rgba[1] = i_comp(norm(((hex >> 16) & 0xFF)));
	rgba[2] = i_comp(norm(((hex >> 8) & 0xFF)));
	rgba[3] = (hex & 0xFF);
}

// MarkMix function
int	gradient(t_dot index, t_dot start, t_dot dest)
{
	float	mix;
	float	s_rgba[4];
	float	d_rgba[4];
	float	i_rgba[4];
	float	brightness;

	mix = get_ratio(index, start, dest);
	hex_to_rgba(start.color, s_rgba);
	hex_to_rgba(dest.color, d_rgba);
	i_rgba[3] = s_rgba[3] + (d_rgba[3] - s_rgba[3]) * mix;
	i_rgba[0] = intrp(s_rgba[0], d_rgba[0], mix);
	i_rgba[1] = intrp(s_rgba[1], d_rgba[1], mix);
	i_rgba[2] = intrp(s_rgba[2], d_rgba[2], mix);
	brightness = intrp(pow(s_rgba[0] + s_rgba[1] + s_rgba[2], GAMMA),
			pow(d_rgba[0] + d_rgba[1] + d_rgba[2], GAMMA), mix);
	if ((i_rgba[0] + i_rgba[1] + i_rgba[2]) != 0)
	{
		mix = pow(brightness, 1 / GAMMA) / (i_rgba[0] + i_rgba[1] + i_rgba[2]);
		i_rgba[0] *= mix;
		i_rgba[1] *= mix;
		i_rgba[2] *= mix;
	}
	return (comp(i_rgba[0]) << 24 | comp(i_rgba[1]) << 16
		| comp(i_rgba[2]) << 8 | (int)i_rgba[3]);
}
