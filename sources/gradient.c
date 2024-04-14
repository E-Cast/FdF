/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 19:10:00 by ecastong          #+#    #+#             */
/*   Updated: 2024/04/13 20:01:51 by ecastong         ###   ########.fr       */
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

// size_t	gradient(t_dot index, t_dot strt, t_dot dest)
// {
// 	float	fraction;
// 	int		rgba[4];

// 	fraction = get_ratio(index, strt, dest);
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

void	extract_rgba(size_t color, float *rgba)
{
	rgba[0] = (color >> 24) & 0xFF;
	rgba[1] = (color >> 16) & 0xFF;
	rgba[2] = (color >> 8) & 0xFF;
	rgba[3] = color & 0xFF;
}

void	normalize_rgba(float *rgba)
{
	rgba[0] = rgba[0] / 255.0;
	rgba[1] = rgba[1] / 255.0;
	rgba[2] = rgba[2] / 255.0;
	rgba[3] = rgba[3] / 255.0;
}

float	inverse_srgb_companding(float n)
{
	if (n <= 0.04045)
		return (n / 12.92);
	else
		return (pow((n + 0.055) / 1.055, 2.4));
}

size_t	gradient(t_dot index, t_dot start, t_dot dest)
{
	float	start_color[4];
	float	dest_color[4];
	float	ratio;
	float	color[4];

	extract_rgba(start.color, start_color);
	printf("%f/%f/%f/%f\n", start_color[0], start_color[1], start_color[2], start_color[3]);
	extract_rgba(dest.color, dest_color);
	ratio = get_ratio(index, start, dest);
	normalize_rgba(start_color);
	printf("%f/%f/%f/%f\n\n", start_color[0], start_color[1], start_color[2], start_color[3]);
	normalize_rgba(dest_color);
	start_color[0] = inverse_srgb_companding(start_color[0]);
	start_color[1] = inverse_srgb_companding(start_color[1]);
	start_color[2] = inverse_srgb_companding(start_color[2]);
	start_color[3] = inverse_srgb_companding(start_color[3]);
	printf("%f/%f/%f/%f\n\n", start_color[0], start_color[1], start_color[2], start_color[3]);
	(void) color;
	(void) ratio;
	return (dest.color);

//    //Apply inverse sRGB companding to convert each channel into linear light
//    r1, g1, b1 ← sRGBInverseCompanding(r1, g1, b1)       
//    r2, g2, b2 ← sRGBInverseCompanding(r2, g2, b2)

//    //Linearly interpolate r, g, b values using mix (0..1)
//    r ← LinearInterpolation(r1, r2, mix)
//    g ← LinearInterpolation(g1, g2, mix)
//    b ← LinearInterpolation(b1, b2, mix)

//    //Compute a measure of brightness of the two colors using empirically determined gamma
//    gamma ← 0.43
//    brightness1 ← Pow(r1+g1+b1, gamma)
//    brightness2 ← Pow(r2+g2+b2, gamma)

//    //Interpolate a new brightness value, and convert back to linear light
//    brightness ← LinearInterpolation(brightness1, brightness2, mix)
//    intensity ← Pow(brightness, 1/gamma)

//    //Apply adjustment factor to each rgb value based
//    if ((r+g+b) != 0) then
//       factor ← (intensity / (r+g+b))
//       r ← r * factor
//       g ← g * factor
//       b ← b * factor
//    end if

//    //Apply sRGB companding to convert from linear to perceptual light
//    r, g, b ← sRGBCompanding(r, g, b)

//    //Convert color components from 0..1 to 0..255
//    Result ← MakeColor(r, g, b)
// End Algorithm MarkMix
}
