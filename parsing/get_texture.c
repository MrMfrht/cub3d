/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaher <fdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 13:08:12 by fdaher            #+#    #+#             */
/*   Updated: 2025/10/08 11:11:59 by fdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	is_color(char *line)
{
	if (!line)
		return (0);
	if (line[0] == 'F' || line[0] == 'C')
		return (1);
	return (0);
}

static int	parse_color(char *line, t_texture *node, t_color **color)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	line++;
	while (*line == ' ')
		line++;
	rgb = ft_split(line, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
		return (free_array(rgb), free_texture(node),
			printf("Error\nbad form(a,b,c)"), -1);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	free_array(rgb);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (free_texture(node), printf("Error\n colorout of range\n"), -1);
	*color = malloc(sizeof(t_color));
	if (!*color)
		return (free_texture(node), printf("Error\n malloc of color\n"), -1);
	(*color)->red = r;
	(*color)->green = g;
	(*color)->blue = b;
	return (0);
}

static int	parse_texture_path(char *line, t_texture *node, char **texture)
{
	char	*start;
	char	*trim;
	int		fd;

	if (!line || !texture)
		return (-1);
	start = line + 2;
	while (*start == ' ')
		start++;
	trim = ft_strtrim(start, " ");
	if (!check_xpm(trim))
		return (free_texture(node),
			printf("Error\n\"%s\" Not .xpm file\n", trim), free(trim), -1);
	fd = open(trim, O_RDONLY);
	if (fd < 0)
		return (close(fd), free_texture(node), free(line),
			printf("Error\nthe \"%s\" can't open\n", trim), free(trim), -1);
	close(fd);
	*texture = trim;
	return (0);
}

static int	parse_line_texture(char *line, t_texture *node)
{
	if (ft_strncmp(line, "NO", 2) == 0)
		return (parse_texture_path(line, node, &node->no));
	else if (ft_strncmp(line, "SO", 2) == 0)
		return (parse_texture_path(line, node, &node->so));
	else if (ft_strncmp(line, "WE", 2) == 0)
		return (parse_texture_path(line, node, &node->we));
	else if (ft_strncmp(line, "EA", 2) == 0)
		return (parse_texture_path(line, node, &node->ea));
	else if (is_color(line) && line[0] == 'F')
		return (parse_color(line, node, &node->f));
	else if (is_color(line) && line[0] == 'C')
		return (parse_color(line, node, &node->c));
	else if (line[0] != '\n')
	{
		printf("Error\n\"%c\" not texture charactere\n", line[0]);
		free_texture(node);
		return (-1);
	}
	return (0);
}

// get the no so we ea f c and check
int	get_texture(char **array, t_texture *node)
{
	int		i;
	char	*line;
	int		j;

	i = 0;
	j = 1;
	if (!array || !node)
		return (printf("Error\n invalid arg in get_texture"), -1);
	while (array[i] && array[i][0] != '1')
	{
		line = ft_strtrim(array[i], " ");
		j = parse_line_texture(line, node);
		free(line);
		if (j < 0)
			return (-1);
		i++;
	}
	return (check_all_texture(node));
}
// int	get_texture(char **array, t_texture *node)
// {
// 	int		i;
// 	char	*line;
// 	int		j;

// 	i = 0;
// 	j = 1;
// 	if (!array || !node)
// 		return (printf("Error\n invalid arg in get_texture"), -1);
// 	while (array[i] && array[i][0] != '1')
// 	{
// 		line = ft_strtrim(array[i], " ");
// 		if (ft_strncmp(line, "NO", 2) == 0)
// 			j = parse_texture_path(line, node, &node->no);
// 		else if (ft_strncmp(line, "SO", 2) == 0)
// 			j = parse_texture_path(line, node, &node->so);
// 		else if (ft_strncmp(line, "WE", 2) == 0)
// 			j = parse_texture_path(line, node, &node->we);
// 		else if (ft_strncmp(line, "EA", 2) == 0)
// 			j = parse_texture_path(line, node, &node->ea);
// 		else if (is_color(line) && line[0] == 'F')
// 			j = parse_color(line, node, &node->f);
// 		else if (is_color(line) && line[0] == 'C')
// 			j = parse_color(line, node, &node->c);
// 		else if (line[0] != '\n')
// 			return (free_texture(node),
// 				printf("Error\n\"%c\" not texture", line[0]), free(line), -1);
// 		free(line);
// 		if (j < 0)
// 			return (-1);
// 		i++;
// 	}
// 	return (check_all_texture(node));
// }

// void	put_texture(char *line, t_texture *node)
// {
// 	int		i;
// 	char	*start;
// 	char	*text;

// 	i = 1;
// 	start = line;
// 	if (!node)
// 		return ;
// 	if (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0
// 		|| ft_strncmp(line, "WE", 2) == 0 || ft_strncmp(line, "EA", 2) == 0)
// 	{
// 		start = start + 2;
// 		i = 2;
// 	}
// 	else
// 		start++;
// 	while (*start == ' ')
// 		start++;
// 	text = ft_strdup(start);
// 	free(line);
// 	if (i == 1)
// 		// split nb
// 		else
// 	// text
// }

// !!!!!!!!!!!!!!!!!i work
// int	get_texture(char **array, t_texture *node)
// {
// 	int		i;
// 	char	*line;

// 	i = 0;
// 	flag = 0;
// 	if (!node)
// 		return (put_error("Error! no texture_node"), -1);
// 	while (array[i])
// 	{
// 		line = ft_strtrim(array[i], " ");
// 		if (line[0] == '\n')
// 		{
// 			i++;
// 			free(line);
// 			continue ;
// 		}
// 		else if ()
// 		{
// 			// put the texture
// 		}
// 		else if (flag < 4 || (flag = 4 && line[0] != 1))
// 			// return(free(line), ,put_error("Error\n you need 4 textures!");
// 			free(line)
// 	}
// 	return (i);
// }

// int main(int argc, char **argv)
// {
//     (void) argc;
//     char **array;

//     array = read_from_file(argv[1]);
//     printf ("%d", get_texture(array, NULL));
// }