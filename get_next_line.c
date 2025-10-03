/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaher <fdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:56:58 by fdaher            #+#    #+#             */
/*   Updated: 2024/07/16 12:39:31 by fdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_copy(t_list *list, char *s)
{
	int	i;
	int	j;

	j = 0;
	while (list)
	{
		i = 0;
		while (list -> buf[i])
		{
			if (list -> buf[i] == '\n')
			{
				s[j] = '\n';
				s[j + 1] = '\0';
				return ;
			}
			s[j++] = list -> buf[i++];
		}
		list = list -> next;
	}
	s[j] = '\0';
}

char	*ft_get_line(t_list *list)
{
	int		lenline;
	char	*line;

	if (list == NULL)
		return (NULL);
	lenline = ft_lenline(list);
	line = (char *)malloc(sizeof(char) * (lenline + 1));
	if (!line)
		return (NULL);
	ft_copy(list, line);
	return (line);
}

void	free_every_node(t_list **list, t_list *reste_node, char *buffer)
{
	t_list	*tmp;

	if (list == NULL)
		return ;
	while (*list)
	{
		tmp = (*list)-> next;
		free((*list)-> buf);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
	if (reste_node -> buf[0])
		*list = reste_node;
	else
	{
		free(buffer);
		free(reste_node);
	}
}

void	ft_reste_node(t_list **list)
{
	int		i;
	int		j;
	char	*buffer;
	t_list	*last_node;
	t_list	*reste_node;

	buffer = (char *)malloc(sizeof(char) *(BUFFER_SIZE + 1));
	reste_node = (t_list *)malloc(sizeof(t_list));
	if (!buffer || !reste_node)
		return ;
	i = 0;
	j = 0;
	last_node = ft_last_node(*list);
	while (last_node -> buf[i] && last_node -> buf[i] != '\n')
		i++;
	if (last_node -> buf[i] == '\n')
		i++;
	while (last_node -> buf[i])
		buffer[j++] = last_node -> buf[i++];
	buffer[j] = '\0';
	reste_node -> buf = buffer;
	reste_node -> next = NULL;
	free_every_node(list, reste_node, buffer);
}

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ft_creat_list(&list, fd);
	if (list == NULL)
		return (NULL);
	line = ft_get_line(list);
	ft_reste_node(&list);
	return (line);
}

// #include <unistd.h>
// #include <fcntl.h>
// #include <stdio.h>

// int	main(void)
// {
// 	int		fd;
// 	int		i;

// 	i = 1;
// 	fd = open("./test.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("Failed to open file");
// 		return (1);
// 	}
// 	char *test = get_next_line(fd);
// 	while (test)
// 	{
// 		printf("line %d %s",i, test);
// 		free(test);
// 		i++;
// 		test = get_next_line(fd);
// 	}
// 	return 0;
// }