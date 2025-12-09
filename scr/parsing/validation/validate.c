/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaher <fdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:49:57 by fdaher            #+#    #+#             */
/*   Updated: 2025/12/09 16:26:21 by fdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3d.h"

static int	floodfill(char **map, int x, int y, t_dim *dim)
{
	if (x < 0 || x >= dim->width || y < 0 || y >= dim->height)
		return (0);
	if (map[y][x] == ' ' || map[y][x] == '\0')
		return (0);
	if (map[y][x] == '1' || map[y][x] == 'F')
		return (1);
	map[y][x] = 'F';
	if (!floodfill(map, x + 1, y, dim))
		return (0);
	if (!floodfill(map, x - 1, y, dim))
		return (0);
	if (!floodfill(map, x, y + 1, dim))
		return (0);
	if (!floodfill(map, x, y - 1, dim))
		return (0);
	return (1);
}

static int	validate_map_borders(char **map)
{
	char	**map_copy;
	int		player_x;
	int		player_y;
	t_dim	dim;
	int		result;

	map_copy = duplicate_map(map);
	if (!map_copy)
		return (0);
	if (!find_player_position(map, &player_x, &player_y))
	{
		free_map(map_copy);
		return (0);
	}
	dim.width = map_max_width(map);
	dim.height = map_height(map);
	result = floodfill(map_copy, player_x, player_y, &dim);
	free_map(map_copy);
	return (result == 1);
}

int	validate_map(char **map)
{
	pad_map_with_spaces(map);
	if (!validate_characters_and_player(map))
		return (0);
	if (!validate_map_borders(map))
		return (printf("Error\n Invaled map borders or player's path\\n"), 0);
	return (1);
}
