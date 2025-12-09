/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaher <fdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 16:30:00 by fdaher            #+#    #+#             */
/*   Updated: 2025/12/09 16:53:07 by fdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3d.h"

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
