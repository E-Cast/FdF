/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 19:10:00 by ecastong          #+#    #+#             */
/*   Updated: 2024/04/13 21:53:03 by ecastong         ###   ########.fr       */
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








// void	extract_rgba(size_t color, float *rgba)
// {
// 	rgba[0] = (color >> 24) & 0xFF;
// 	rgba[1] = (color >> 16) & 0xFF;
// 	rgba[2] = (color >> 8) & 0xFF;
// 	rgba[3] = color & 0xFF;
// }

// void	normalize_rgba(float *rgba)
// {
// 	rgba[0] = rgba[0] / 255.0;
// 	rgba[1] = rgba[1] / 255.0;
// 	rgba[2] = rgba[2] / 255.0;
// 	rgba[3] = rgba[3] / 255.0;
// }

// void	inverse_srgb_companding(float *rgba)
// {
// 	if (rgba[0] <= 0.04045)
// 		rgba[0] = (rgba[1] / 12.92);
// 	else
// 		rgba[0] = (pow((rgba[0] + 0.055) / 1.055, 2.4));
// 	if (rgba[1] <= 0.04045)
// 		rgba[1] = (rgba[1] / 12.92);
// 	else
// 		rgba[1] = (pow((rgba[1] + 0.055) / 1.055, 2.4));
// 	if (rgba[2] <= 0.04045)
// 		rgba[2] = (rgba[2] / 12.92);
// 	else
// 		rgba[2] = (pow((rgba[2] + 0.055) / 1.055, 2.4));
// 	if (rgba[3] <= 0.04045)
// 		rgba[3] = (rgba[3] / 12.92);
// 	else
// 		rgba[3] = (pow((rgba[3] + 0.055) / 1.055, 2.4));
// }

// float	linear_interpolation(float a, float b, float ratio)
// {
// 	return (a * (1.0f - ratio) + b * ratio);
// }

// void	interpolate_color(float *strt, float *end, float *rgba, float mix)
// {
// 	// rgba[0] = strt[0] * (1.0f - mix) + end[0] * mix;
// 	// rgba[1] = strt[1] * (1.0f - mix) + end[1] * mix;
// 	// rgba[2] = strt[2] * (1.0f - mix) + end[2] * mix;
// 	// rgba[3] = strt[3] * (1.0f - mix) + end[3] * mix;
// 	rgba[0] = linear_interpolation(strt[0], end[0], mix);
// 	rgba[1] = linear_interpolation(strt[1], end[1], mix);
// 	rgba[2] = linear_interpolation(strt[2], end[2], mix);
// 	rgba[3] = linear_interpolation(strt[3], end[3], mix);
// }

// float	to_sRGB_f(float x)
// {
// 	if (x <= 0.0031308)
// 		return (12.92 * x);
// 	else
// 		return ((1.055 * powf(x, 1.0f / 2.4f)) - 0.055);
// }

// size_t	gradient(t_dot index, t_dot start, t_dot dest)
// {
// 	float	start_color[4];
// 	float	dest_color[4];
// 	float	ratio;
// 	float	color[4];
// 	float	gamma;
// 	float	brightness1;
// 	float	brightness2;
// 	float	brightness;
// 	float	intensity;
// 	float	factor;

// 	extract_rgba(start.color, start_color);
// 	extract_rgba(dest.color, dest_color);
// 	printf("%f/%f/%f/%f\n", start_color[0], start_color[1], start_color[2], start_color[3]);
// 	ratio = get_ratio(index, start, dest);
// 	normalize_rgba(start_color);
// 	normalize_rgba(dest_color);
// 	printf("%f/%f/%f/%f\n", start_color[0], start_color[1], start_color[2], start_color[3]);
// 	inverse_srgb_companding(start_color);
// 	inverse_srgb_companding(dest_color);
// 	printf("%f/%f/%f/%f\n", start_color[0], start_color[1], start_color[2], start_color[3]);
// 	interpolate_color(start_color, dest_color, color, ratio);
// 	printf("%f/%f/%f/%f\n\n", color[0], color[1], color[2], color[3]);
// 	gamma = 0.43;
// 	brightness1 = pow(start_color[0] + start_color[1] + start_color[2], gamma);
// 	brightness2 = pow(dest_color[0] + dest_color[1] + dest_color[2], gamma);
// 	brightness = linear_interpolation(brightness1, brightness2, 1 / gamma);
// 	intensity = pow(brightness, 1 / gamma);
// 	printf("%f/%f\n\n", brightness, intensity);
// 	if ((color[0] + color[1] + color[2]) != 0)
// 	{
// 		factor = intensity / (color[0] + color[1] + color[2]);
// 		color[0] = color[0] * factor;
// 		color[1] = color[1] * factor;
// 		color[2] = color[2] * factor;
// 	}
// 	inverse_srgb_companding(color);
// 	color[0] = (size_t)(255.9999 * to_sRGB_f(color[0]));
// 	color[1] = (size_t)(255.9999 * to_sRGB_f(color[1]));
// 	color[2] = (size_t)(255.9999 * to_sRGB_f(color[2]));
// 	printf("%lx\n", ((size_t)color[0] << 24 | (size_t)color[1] << 16 | (size_t)color[2] << 8 | 0xFF));
// 	return ((size_t)color[0] << 24 | (size_t)color[1] << 16 | (size_t)color[2] << 8 | 0xFF);
// }

// Function to normalize RGB values from 0..255 to 0..1
void Normalize(uint8_t r, uint8_t g, uint8_t b, float *r1, float *g1, float *b1) {
    *r1 = r / 255.0f;
    *g1 = g / 255.0f;
    *b1 = b / 255.0f;
}

// Function to apply inverse sRGB companding
void sRGBInverseCompanding(float r, float g, float b, float *r1, float *g1, float *b1) {
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
void MarkMix(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, float mix, uint8_t *result_r, uint8_t *result_g, uint8_t *result_b) {
    float r1_norm, g1_norm, b1_norm;
    float r2_norm, g2_norm, b2_norm;
    float r, g, b;
    float brightness1, brightness2, brightness;
    float intensity;
    float factor;

    // Normalize colors
    Normalize(r1, g1, b1, &r1_norm, &g1_norm, &b1_norm);
    Normalize(r2, g2, b2, &r2_norm, &g2_norm, &b2_norm);

    // Apply inverse sRGB companding
    sRGBInverseCompanding(r1_norm, g1_norm, b1_norm, &r1_norm, &g1_norm, &b1_norm);
    sRGBInverseCompanding(r2_norm, g2_norm, b2_norm, &r2_norm, &g2_norm, &b2_norm);

    // Linearly interpolate r, g, b values
    r = LinearInterpolation(r1_norm, r2_norm, mix);
    g = LinearInterpolation(g1_norm, g2_norm, mix);
    b = LinearInterpolation(b1_norm, b2_norm, mix);

    // Compute brightness
    float gamma = 0.43;
    brightness1 = pow(r1_norm + g1_norm + b1_norm, gamma);
    brightness2 = pow(r2_norm + g2_norm + b2_norm, gamma);

    // Interpolate brightness and adjust intensity
    brightness = LinearInterpolation(brightness1, brightness2, mix);
    intensity = pow(brightness, 1 / gamma);

    // Adjustment factor
    if ((r + g + b) != 0) {
        factor = intensity / (r + g + b);
        r *= factor;
        g *= factor;
        b *= factor;
    }

    // Apply sRGB companding
    sRGBCompanding(r, g, b, result_r, result_g, result_b);
}

size_t	gradient(t_dot index, t_dot start, t_dot dest)
{
	uint8_t	r1 = ((start.color >> 24) & 0xFF);
	uint8_t	g1 = ((start.color >> 16) & 0xFF);
	uint8_t	b1 = ((start.color >> 8) & 0xFF);
	uint8_t	r2 = ((dest.color >> 24) & 0xFF);
	uint8_t	g2 = ((dest.color >> 16) & 0xFF);
	uint8_t	b2 = ((dest.color >> 8) & 0xFF);
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	float	mix = get_ratio(index, start, dest);

	MarkMix(r1, g1, b1, r2, g2, b2, mix, &r, &g, &b);
	return (r << 24 | g << 16 | b << 8 | 0xFF);
}