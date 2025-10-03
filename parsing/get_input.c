/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaher <fdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:07:24 by fdaher            #+#    #+#             */
/*   Updated: 2025/09/30 14:33:07 by fdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_cub(char *str)
{
	char	*extension;

	extension = ft_strrchr(str, '.');
	if (!extension)
		return (0);
	if (ft_strncmp(extension, ".cub", 4) == 0)
		return (1);
	return (0);
}

// free array
void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static char	**array_join_null(char *str_add)
{
	char	**res;

	res = (char **)malloc(sizeof(char *) * 2);
	if (!res)
		return (NULL);
	res[0] = ft_strdup(str_add);
	res[1] = NULL;
	return (res);
}

// add (char *)str to (char **)array (comme str_join) 
char	**array_join(char **old_array, char *str_add)
{
	char	**res;
	int		count;

	count = 0;
	if (old_array == NULL)
		return (array_join_null(str_add));
	while (old_array[count] != NULL)
		count++;
	res = (char **)malloc(sizeof(char *) * (count + 2));
	if (!res)
		return (NULL);
	count = 0;
	while (old_array[count])
	{
		res[count] = ft_strdup(old_array[count]);
		count++;
	}
	res[count] = ft_strdup(str_add);
	res[count + 1] = NULL;
	free_array(old_array);
	return (res);
}

// read all the file with spaces and \n 
char	**read_from_file(const char *s)
{
	char	**arr;
	char	*line;
	int		fd;

	arr = NULL;
	fd = open(s, O_RDONLY);
	if (fd < 0)
		return (close(fd), ft_putstr_fd("Error!open_file", 2), NULL);
	line = get_next_line(fd);
	while (line)
	{
		arr = array_join(arr, line);
		free(line);
		line = get_next_line(fd);
	}
	close (fd);
	return (arr);
}

// int main(int argc, char **argv)
// {
// 	int i = 0;
// 	char **array;

// 	(void) argc;
// 	array = read_from_file(argv[1]);
// 	while (array[i])
// 	{
// 		printf("%s",array[i]);
// 		i++;
// 	}
// }
