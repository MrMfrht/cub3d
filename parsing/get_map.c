/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaher <fdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 11:01:47 by fdaher            #+#    #+#             */
/*   Updated: 2025/10/08 13:04:33 by fdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (1);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

static int	is_valid_map_char(char c)
{
	if (c == ' ' || c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W')
		return (1);
	return (0);
}

static int	is_invalid_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!is_valid_map_char(line[i]) && line[i] != '\t' && line[i] != '\n')
			return (1);
		i++;
	}
	return (0);
}

char	**get_map(char **input)
{
	int		i;
	int		j;
	char	**map;
	int		in_map;

	i = 0;
	map = NULL;
	in_map = 0;
	while (input[i])
	{
		j = 0;
		if (input[i][0] == '1')
			in_map = 1;
		if (in_map)
		{
			if (is_empty_line(input[i]) && !is_empty_line(input[i + 1]))
				return (printf("Error\nEmptyline map\n"), free_array(map),
					NULL);
			if (is_invalid_line(input[i]))
				return (printf("Error\nInvalid character in map line: \"%s\"\n",
						input[i]), free_array(map), NULL);
			while (input[i][j] == ' ' || input[i][j] == '\t')
				j++;
			if (input[i][j] == '1' || input[i][j] == '0')
				map = array_join(map, input[i]);
		}
		i++;
	}
	if (!map)
		printf("Error\nNo map found\n");
	return (map);
}

// char	**get_map(char **input)
// {
// 	char	**map;

// 	return (map);
// }
