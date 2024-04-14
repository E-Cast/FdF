/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 19:10:00 by ecastong          #+#    #+#             */
/*   Updated: 2024/04/13 22:27:36 by ecastong         ###   ########.fr       */
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







// Function to normalize RGB values from 0..255 to 0..1
void Normalize(uint8_t r, uint8_t g, uint8_t b, float *r1, float *g1, float *b1)
{
	*r1 = r / 255.0f;
	*g1 = g / 255.0f;
	*b1 = b / 255.0f;
}

// Function to apply inverse sRGB companding
void sRGBInverseCompanding(float r, float g, float b, float *r1, float *g1, float *b1)
{
	if (r <= 0.04045)
		*r1 = r / 12.92;
	else
		*r1 = pow((r + 0.055) / 1.055, 2.4);

	if (g <= 0.04045)
		*g1 = g / 12.92;
	else
		*g1 = pow((g + 0.055) / 1.055, 2.4);

	if (b <= 0.04045)
		*b1 = b / 12.92;
	else
		*b1 = pow((b + 0.055) / 1.055, 2.4);
}

// Function for linear interpolation
float LinearInterpolation(float a, float b, float mix) {
	return a * (1 - mix) + b * mix;
}

// Function to apply sRGB companding
void sRGBCompanding(float r, float g, float b, uint8_t *r1, uint8_t *g1, uint8_t *b1) {
	if (r <= 0.0031308)
		*r1 = (r * 12.92) * 255;
	else
		*r1 = (1.055 * pow(r, 1 / 2.4) - 0.055) * 255;

	if (g <= 0.0031308)
		*g1 = (g * 12.92) * 255;
	else
		*g1 = (1.055 * pow(g, 1 / 2.4) - 0.055) * 255;

	if (b <= 0.0031308)
		*b1 = (b * 12.92) * 255;
	else
		*b1 = (1.055 * pow(b, 1 / 2.4) - 0.055) * 255;
}

// Function to make a color from RGB values
void MakeColor(float r, float g, float b, uint8_t *r1, uint8_t *g1, uint8_t *b1) {
	*r1 = r * 255;
	*g1 = g * 255;
	*b1 = b * 255;
}

// Main MarkMix function
void MarkMix(uint8_t *rgb1, uint8_t *rgb2, float mix, uint8_t *result)
{
	float	norm1[3];
	float	norm2[3];
	float	rgb[3];
	float	brightness[3];
	float	intensity;
	float	factor;

	// Normalize colors
	Normalize(rgb1[0], rgb1[1], rgb1[2], &norm1[0], &norm1[1], &norm1[2]);
	Normalize(rgb2[0], rgb2[1], rgb2[2], &norm2[0], &norm2[1], &norm2[2]);
	// Apply inverse sRGB companding
	sRGBInverseCompanding(norm1[0], norm1[1], norm1[2], &norm1[0], &norm1[1], &norm1[2]);
	sRGBInverseCompanding(norm2[0], norm2[1], norm2[2], &norm2[0], &norm2[1], &norm2[2]);
	// Linearly interpolate r, g, b values
	rgb[0] = LinearInterpolation(norm1[0], norm2[0], mix);
	rgb[1] = LinearInterpolation(norm1[1], norm2[1], mix);
	rgb[2] = LinearInterpolation(norm1[2], norm2[2], mix);
	// Compute brightness

	brightness[1] = pow(norm1[0] + norm1[1] + norm1[2], GAMMA);
	brightness[2] = pow(norm2[0] + norm2[1] + norm2[2], GAMMA);
	// Interpolate brightness and adjust intensity
	brightness[0] = LinearInterpolation(brightness[1], brightness[2], mix);
	intensity = pow(brightness[0], 1 / GAMMA);
	// Adjustment factor
	if ((rgb[0] + rgb[1] + rgb[2]) != 0)
	{
		factor = intensity / (rgb[0] + rgb[1] + rgb[2]);
		rgb[0] *= factor;
		rgb[1] *= factor;
		rgb[2] *= factor;
	}
	// Apply sRGB companding
	sRGBCompanding(rgb[0], rgb[1], rgb[2], &result[0], &result[1], &result[2]);
}

size_t	gradient(t_dot index, t_dot start, t_dot dest)
{
	uint8_t	rgb1[3];
	uint8_t	rgb2[3];
	float	mix;
	uint8_t	result[3];

	rgb1[0] = ((start.color >> 24) & 0xFF);
	rgb1[1] = ((start.color >> 16) & 0xFF);
	rgb1[2] = ((start.color >> 8) & 0xFF);
	rgb2[0] = ((dest.color >> 24) & 0xFF);
	rgb2[1] = ((dest.color >> 16) & 0xFF);
	rgb2[2] = ((dest.color >> 8) & 0xFF);
	mix = get_ratio(index, start, dest);
	MarkMix(rgb1, rgb2, mix, result);
	return (result[0] << 24 | result[1] << 16 | result[2] << 8 | 0xFF);
}
