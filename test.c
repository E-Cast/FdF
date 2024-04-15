/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 07:28:10 by ecastong          #+#    #+#             */
/*   Updated: 2024/04/15 08:00:43 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <libft.h>

t_dot	*make_dot(char *raw_dot, int x, int y, size_t default_color)
{
	t_dot	*new_dot;

	new_dot = ft_calloc(1, sizeof(t_dot));
	if (new_dot == NULL)
		return (NULL);
	new_dot->x = x;
	new_dot->y = y;
	new_dot->z = ft_atoi(raw_dot);
	while (*raw_dot && my_isspace(*raw_dot) != 0)
		raw_dot++;
	while (*raw_dot && (my_isspace(*raw_dot) == 0 && *raw_dot != ','))
		raw_dot++;
	new_dot->color = default_color;
	if (*raw_dot != ',')
		return (new_dot);
	raw_dot++;
	if (*raw_dot && *raw_dot == '0' && (*raw_dot + 1 == 'x' || *raw_dot + 1 == 'X'))
		raw_dot += 2;
	while (*raw_dot && *raw_dot != ' ')
	{
		new_dot->color = (new_dot->color * 16 + my_hexchar_to_int(*raw_dot));
		raw_dot++;
	}
	return (new_dot);
}

int	main(void)
{
	char	*hex;
	int		out;
	int		i;

	hex = ft_strdup("0x11223300");
	out = 0x000000;
	i = 0;
	if (hex[i] && hex[i] == '0' && (hex[i + 1] == 'x' || hex[i + 1] == 'X'))
		i += 2;
	hex += i;
	i = 0;
	printf("s:%s\ni:%i\nx:%x\n\n", hex, out, out);
	while (hex[i] && hex[i] != ' ')
	{
		out = (out * 16 + my_hexchar_to_int(hex[i++]));
		printf("s:%s\ni:%i\nx:%x\n\n", hex, out, out);
	}
}
