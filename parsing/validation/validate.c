/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaher <fdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:49:57 by fdaher            #+#    #+#             */
/*   Updated: 2025/10/21 10:20:48 by fdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	map_max_width(char **map)
{
	int	i;
	int	max_width;
	int	current_width;

	i = 0;
	max_width = 0;
	while (map[i])
	{
		current_width = ft_strlen(map[i]);
		if (current_width > max_width)
			max_width = current_width;
		i++;
	}
	return (max_width);
}

int	map_height(char **map)
{
	int	height;

	height = 0;
	while (map[height])
		height++;
	return (height);
}

char	*pad_line_with_spaces(char *line, int max_map_width)
{
	char	*padded;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(line);
	padded = malloc(max_map_width + 1);
	if (!padded)
		return (NULL);
	while (i < max_map_width)
	{
		if (i < len)
			padded[i] = line[i];
		else
			padded[i] = ' ';
		i++;
	}
	padded[i] = '\0';
	return (padded);
}

void	pad_map_with_spaces(char **map)
{
	int		i;
	int		max_width;
	char	*padded_line;

	i = 0;
	max_width = map_max_width(map);
	while (map[i])
	{
		padded_line = pad_line_with_spaces(map[i], max_width);
		if (padded_line)
		{
			free(map[i]);
			map[i] = padded_line;
		}
		i++;
	}
}

int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W');
}

int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	validate_characters_and_player(char **map)
{
	int i;
	int	j;
	int	player_count;

	i = 0;
	player_count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!is_valid_char(map[i][j]))
				return (printf("Error\nInvalid charactere %c\n", map[i][j]), 0);
			if (is_player_char(map[i][j]))
				player_count++;
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return (printf("Error\nThe number of player must be 1\n"), 0);
	return (1);
}

int	floodfill(char **map, int x, int y, int width, int height)
{
	if (x < 0 || x >= width || y < 0 || y >= height)
		return (0);
	if (map[y][x] == ' ' || map[y][x] == '\0')
		return (0);
	if (map[y][x] == '1' || map[y][x] == 'F')
		return (1);
	map[y][x] = 'F';
	if (!floodfill(map, x + 1, y, width, height))
		return (0);
	if (!floodfill(map, x - 1, y, width, height))
		return (0);
	if (!floodfill(map, x, y + 1, width, height))
		return (0);
	if (!floodfill(map, x, y - 1, width, height))
		return (0);
	return (1);
}

char	**duplicate_map(char **map)
{
	char	**dup;
	int		height;
	int		i;

	height = map_height(map);
	dup = malloc(sizeof(char *) * (height + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < height)
	{
		dup[i] = ft_strdup(map[i]);
		if (!dup[i])
		{
			while (--i >= 0)
				free(dup[i]);
			free(dup);
			return (NULL);
		}
		i++;
	}
	dup[i] = NULL;
	return (dup);
}

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	find_player_position(char **map, int *x, int *y)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_player_char(map[i][j]))
			{
				*x = j;
				*y = i;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	validate_map_borders(char **map)
{
	char	**map_copy;
	int		player_x;
	int		player_y;
	int		width;
	int		height;
	int		result;

	map_copy = duplicate_map(map);
	if (!map_copy)
		return (0);
	if (!find_player_position(map, &player_x, &player_y))
	{
		free_map(map_copy);
		return (0);
	}
	width = map_max_width(map);
	height = map_height(map);
	result = floodfill(map_copy, player_x, player_y, width, height);
	free_map(map_copy);
	return (result == 1);
}

int	validate_map(char **map)
{
	pad_map_with_spaces(map);
	if (!validate_characters_and_player(map))
		return (0);
	if (!validate_map_borders(map))
		return (printf("Error\n Invaled map borders or player's path\n"), 0);
	return (1);
}
