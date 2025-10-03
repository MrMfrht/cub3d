#include "../cub3d.h"

int map_max_width(t_cub cub)
{
	int	i;
	int	max_width;
	int	current_width;

	i = 0;
	max_width = 0;
	while (cub.map[i])
	{
		current_width = ft_strlen(cub.map[i]);
		if (current_width > max_width)
			max_width = current_width;
		i++;
	}
	return (max_width);
}

int map_height(t_cub cub)
{
	int	height;

	height = 0;
	while (cub.map[height])
		height++;
	return (height);
}

char *pad_line_with_spaces(char *line, int max_map_width)
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

void pad_map_with_spaces(t_cub *cub)
{
	int		i;
	int		max_width;
	char	*padded_line;

	i = 0;
	max_width = map_max_width(*cub);
	while (cub->map[i])
	{
		padded_line = pad_line_with_spaces(cub->map[i], max_width);
		if (padded_line)
		{
			free(cub->map[i]);
			cub->map[i] = padded_line;
		}
		i++;
	}
}

int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' ||
			c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	validate_characters_and_player(t_cub *cub)
{
	int	i;
	int	j;
	int	player_count;

	i = 0;
	player_count = 0;
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (!is_valid_char(cub->map[i][j]))
				return (0);
			if (is_player_char(cub->map[i][j]))
				player_count++;
			j++;
		}
		i++;
	}
	return (player_count == 1);
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

char	**duplicate_map(t_cub *cub)
{
	char	**dup;
	int		height;
	int		i;

	height = map_height(*cub);
	dup = malloc(sizeof(char *) * (height + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < height)
	{
		dup[i] = ft_strdup(cub->map[i]);
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

int	find_player_position(t_cub *cub, int *x, int *y)
{
	int	i;
	int	j;

	i = 0;
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (is_player_char(cub->map[i][j]))
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

int	validate_map_borders(t_cub *cub)
{
	char	**map_copy;
	int		player_x;
	int		player_y;
	int		width;
	int		height;
	int		result;

	map_copy = duplicate_map(cub);
	if (!map_copy)
		return (0);
	
	if (!find_player_position(cub, &player_x, &player_y))
	{
		free_map(map_copy);
		return (0);
	}
	
	width = map_max_width(*cub);
	height = map_height(*cub);
	
	result = floodfill(map_copy, player_x, player_y, width, height);
	
	free_map(map_copy);
	
	return (result == 1);
}

int	validate_map(t_cub *cub)
{
	pad_map_with_spaces(cub);
	
	if (!validate_characters_and_player(cub))
		return (0);
	
	if (!validate_map_borders(cub))
		return (0);
	
	return (1);
}

