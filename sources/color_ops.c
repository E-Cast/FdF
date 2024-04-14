/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 23:32:18 by ecastong          #+#    #+#             */
/*   Updated: 2024/04/13 23:44:16 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Normalize
float	norm(int n)
{
	return (n / 255.0f);
}

// Linear interpolation
float	intrp(float a, float b, float mix)
{
	return (a * (1 - mix) + b * mix);
}

// sRGBInverseCompandin
float	i_comp(float f)
{
	if (f <= 0.04045)
		return (f / 12.92);
	else
		return (pow((f + 0.055) / 1.055, 2.4));
}

// sRGBCompanding
int	comp(float f)
{
	if (f <= 0.0031308)
		return ((f * 12.92) * 255);
	else
		return ((1.055 * pow(f, 1 / 2.4) - 0.055) * 255);
}
