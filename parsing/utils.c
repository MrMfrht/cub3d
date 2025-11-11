/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 11:01:31 by fdaher            #+#    #+#             */
/*   Updated: 2025/11/11 09:54:21 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// Each color (red, green, blue) is stored on 8 bits
// r (16->23 bits), g (8–>15 bits), b (0->7 bits)
// Move red 16 bits to the left → R00000
// Move green 8 bits → 00G000
// Keep blue as is → 0000B
// Then combine (bitwise OR |) to get: 0xRRGGBB (in decimal form)

static void	rgb_to_int(t_color *color)
{
	if (!color)
		return ;
	color->value = ((color->red << 16) | (color->green << 8) | (color->blue));
	return ;
}

int	check_all_texture(t_texture *node)
{
	if (!node)
		return (printf("Error\n we don't have texture_node"), -1);
	if (!(node->no))
		return (printf("Error\nplease put NO\n"), free_texture(node), -1);
	if (!(node->so))
		return (printf("Error\nplease put SO\n"), free_texture(node), -1);
	if (!(node->we))
		return (printf("Error\nplease put WE\n"), free_texture(node), -1);
	if (!(node->ea))
		return (printf("Error\nplease put EA\n"), free_texture(node), -1);
	if (!(node->f))
		return (printf("Error\nplease put F\n"), free_texture(node), -1);
	if (!(node->c))
		return (printf("Error\nplease put C\n"), free_texture(node), -1);
	rgb_to_int(node->c);
	rgb_to_int(node->f);
	return (0);
}

int	is_valid_map(char **input)
{
	char	**map;

	if (!input)
		return (printf("Error\n invalid arg in is_valid_map\n"), -1);
	map = get_map(input);
	if (!map)
		return (-1);
	if (validate_map(map) == 0)
		return (free_array(map), -1);
	free_array(map);
	return (1);
}

int	find_map_start(char **input)
{
	int		i;
	char	*trim;

	i = 0;
	while (input[i])
	{
		trim = ft_strtrim(input[i], " ");
		if (trim && trim[0] == '1')
		{
			free(trim);
			return (i);
		}
		free(trim);
		i++;
	}
	return (-1);
}
