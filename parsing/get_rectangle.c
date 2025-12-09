/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rectangle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaher <fdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 11:56:26 by fdaher            #+#    #+#             */
/*   Updated: 2025/12/09 15:27:37 by fdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	get_max_len(char **map)
{
	int	i;
	int	len;
	int	max;

	i = 0;
	max = 0;
	if (!map)
		return (0);
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

static void	change_space_to_one(char **map)
{
	int	i;
	int	j;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == ' ')
				map[i][j] = '1';
			j++;
		}
		i++;
	}
}

static char	*complete_by_one(char *line, int max_len)
{
	int		len;
	char	*new;
	int		i;

	len = ft_strlen(line);
	new = (char *) malloc (sizeof(char) * (max_len + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new[i] = line[i];
		i++;
	}
	while (i < max_len)
	{
		new[i] = '1';
		i++;
	}
	new[i] = '\0';
	return (new);
}

// transform the input_valid_map to rectangle shape
char	**get_rectangle_map(char **input)
{
	char	**map;
	char	**rect;
	char	*newline;
	int		max_len;
	int		i;

	rect = NULL;
	i = 0;
	map = get_map(input);
	if (!map)
		return (NULL);
	change_space_to_one(map);
	max_len = get_max_len(map);
	while (map[i])
	{
		newline = complete_by_one(map[i], max_len);
		if (!newline)
			return (free_array(map), free_array(rect), NULL);
		rect = array_join(rect, newline);
		free(newline);
		i++;
	}
	free_array(map);
	return (rect);
}

int	is_border_valid(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

// char	**get_rectangle_map(char **input)
// {
// 	char	**rect;
// 	char	**map;
// 	int		len_max;
// 	map = get_map(input);
// 	change_space_to_one;
// 	rect = add_end_one(map, max_len);
// 	free_array(map);
// 	return (rect);
// }