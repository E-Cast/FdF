/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 23:32:18 by ecastong          #+#    #+#             */
/*   Updated: 2024/04/14 00:59:24 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Normalizes an int ranging from 0 to 
 * 255 to a float ranging from 0 to 1.
 * 
 * @param n Int to normalize.
 * @retval A float ranging from 0 to 1.
 */
float	norm(int n)
{
	return (n / 255.0f);
}

/**
 * @brief Estimates a value between a and b via linear interpolation.
 * 
 * @param a Value a.
 * @param b Value b.
 * @param factor Factor used to determine what to return.
 * @retval A value from ranging from a to b.
 */
float	intrp(float a, float b, float factor)
{
	return (a * (1 - factor) + b * factor);
}

/**
 * @brief Converts a color value from sRGB
 *  to linear light via inverse companding.
 * 
 * @param f Color value to convert.
 * @retval Linearized color value.
 */
float	i_comp(float f)
{
	if (f <= 0.04045)
		return (f / 12.92);
	else
		return (pow((f + 0.055) / 1.055, 2.4));
}

// sRGBCompanding
/**
 * @brief Converts a color value from linear
 *  light to sRGB via companding.
 * 
 * @param f Color value to convert.
 * @retval sRGB color value.
 */
int	comp(float f)
{
	if (f <= 0.0031308)
		return ((f * 12.92) * 255);
	else
		return ((1.055 * pow(f, 1 / 2.4) - 0.055) * 255);
}
