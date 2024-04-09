/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_atoh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 02:34:57 by ecastong          #+#    #+#             */
/*   Updated: 2024/04/06 03:32:22 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	hexchar_to_int(char hex)
{
	if (ft_isdigit(hex))
		return (hex - '0');
	else if (hex >= 'A' && hex <= 'Z')
		return ((hex + 10) - 'A');
	else if (hex >= 'a' && hex <= 'z')
		return ((hex + 10) - 'a');
	return (0);
}

unsigned int	my_atoh(const char *str)
{
	size_t			i;
	unsigned int	num;

	i = 0;
	num = 0;

	while (my_isspace(str[i]))
		i++;
	if (str[i] && str[i] == '0' && (str[i + 1] == 'x' || str[i + 1] == 'X'))
		i += 2;
	while (str[i] && (my_isset(str[i], "0123456789abcdefABCDEF")))
	{
		num = num * 16 + hexchar_to_int(str[i]);
		i++;
	}
	return (num);
}
