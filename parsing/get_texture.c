/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaher <fdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 13:08:12 by fdaher            #+#    #+#             */
/*   Updated: 2025/10/07 13:08:41 by fdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	put_error(char *msg)
{
	ft_putendl_fd(msg, 2);
	exit(1);
}

static int	is_texture(char *line)
{
	if (!line)
		return (-1);
	if (ft_strncmp(line, "NO", 2) == 0)
		return (0);
	if (ft_strncmp(line, "SO", 2) == 0)
		return (0);
	if (ft_strncmp(line, "WE", 2) == 0)
		return (0);
	if (ft_strncmp(line, "EA", 2) == 0)
		return (0);
	if (ft_strncmp(line, "F", 1) == 0)
		return (0);
	if (ft_strncmp(line, "C", 1) == 0)
		return (0);
	return (-1);
}

void	put_nswe(char *test, t_texture *node)
{
	if (!node)
}

void	put_texture(char *line, t_texture *node)
{
	int		i;
	char	*start;
	char	*text;

	i = 1;
	start = line;
	if (!node)
		return ;
	if (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0
		|| ft_strncmp(line, "WE", 2) == 0 || ft_strncmp(line, "EA", 2) == 0)
	{
		start = start + 2;
		i = 2;
	}
	else
		start++;
	while (*start == ' ')
		start++;
	text = ft_strdup(start);
	free(line);
	if (i == 1)
		// split nb
		else
	// text
}

// !!!!!!!!!!!!!!!!!i work
int	get_texture(char **array, t_texture *node)
{
	int		i;
	char	*line;

	i = 0;
	flag = 0;
	if (!node)
		return (put_error("Error! no texture_node"), -1);
	while (array[i])
	{
		line = ft_strtrim(array[i], " ");
		if (line[0] == '\n')
		{
			i++;
			free(line);
			continue;
		}
		else if ()
		{
			// put the texture
		}
		else if (flag < 4 || (flag = 4 && line[0] != 1))
			// return(free(line), ,put_error("Error\n you need 4 textures!");
			free(line)
	}
	return (i);
}

// int main(int argc, char **argv)
// {
//     (void) argc;
//     char **array;

//     array = read_from_file(argv[1]);
//     printf ("%d", get_texture(array, NULL));
// }