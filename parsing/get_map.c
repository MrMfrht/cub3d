/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaher <fdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 11:01:47 by fdaher            #+#    #+#             */
/*   Updated: 2025/10/21 11:48:02 by fdaher           ###   ########.fr       */
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

static int	process_map_line(char **input, int i, char ***map)
{
	char	*trim_line;
	int		j;

	if (is_empty_line(input[i]) && input[i + 1]
		&& !is_empty_line(input[i + 1]))
		return (printf("Error\nEmptyline map\n"), free_array(*map), -1);
	if (is_invalid_line(input[i]))
		return (printf("Error\nInvalid character in map line: \"%s\"\n",
				input[i]), free_array(*map), -1);
	j = 0;
	while (input[i][j] == ' ' || input[i][j] == '\t' || input[i][j] == '\n')
		j++;
	if (input[i][j] == '1')
	{
		trim_line = ft_strtrim(input[i], " ");
		if (trim_line[ft_strlen(trim_line) - 1] != '1')
			return (printf("Error\nMap not closed: %s\n", trim_line),
				free(trim_line), free_array(*map), -1);
		free (trim_line);
		*map = array_join(*map, input[i]);
	}
	else if (input[i][j])
		return (printf("Error\nthe map not closed: %s\n", input[i]),
			free_array(*map), -1);
	return (0);
}

// get the map if it doesn't contain \n and starting by 1 
char	**get_map(char **input)
{
	int		i;
	char	**map;

	i = 0;
	map = NULL;
	i = find_map_start(input);
	if (i < 0 || !input[i])
		return (printf("Error\nNo map found\n"), NULL);
	while (input[i])
	{
		if (process_map_line(input, i, &map) < 0)
			return (NULL);
		i++;
	}
	return (map);
}

// char	**get_map(char **input)
// {
// 	int		i;
// 	char	**map;
// 	char	*line_input;

// 	i = 0;
// 	map = NULL;
// 	while (input[i])
// 	{
// 		line_input = ft_strtrim(input[i], " ");
// 		if (line_input[0] == '1')
// 		{
// 			free(line_input);
// 			break ;
// 		}
// 		free(line_input);
// 		i++;
// 	}
// 	if (!input[i])
// 		return (printf("Error\nNo map found\n"), NULL);
// 	while (input[i])
// 	{
// 		if (process_map_line(input, i, &map) < 0)
// 			return (NULL);
// 		i++;
// 	}
// 	return (map);
// }

// char	**get_map(char **input)
// {
// 	int		i;
// 	char	**map;
// 	int		in_map;

// 	i = 0;
// 	map = NULL;
// 	in_map = 0;
// 	while (input[i])
// 	{
// 		if (input[i][0] == '1')
// 			in_map = 1;
// 		if (in_map)
// 		{
// 			if (process_map_line(input, i, &map) < 0)
// 				return (NULL);
// 		}
// 		i++;
// 	}
// 	if (!map)
// 		printf("Error\nNo map found\n");
// 	return (map);
// }
