/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaher <fdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:57:44 by fdaher            #+#    #+#             */
/*   Updated: 2024/07/11 14:39:55 by fdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_last_node(t_list *list)
{
	if (list == NULL)
		return (NULL);
	while (list -> next)
		list = list -> next;
	return (list);
}

int	ft_found_newligne(t_list *list)
{
	int	i;

	if (list == NULL)
		return (0);
	while (list)
	{
		i = 0;
		while (list -> buf[i] && i < BUFFER_SIZE)
		{
			if (list -> buf[i] == '\n')
				return (1);
			i++;
		}
		list = list -> next;
	}
	return (0);
}

void	ft_connect_node(t_list	**list, char *buffer)
{
	t_list	*new_node;
	t_list	*last_node;

	last_node = ft_last_node(*list);
	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return ;
	if (last_node == NULL)
		*list = new_node;
	else
		last_node -> next = new_node;
	new_node -> buf = buffer;
	new_node -> next = NULL;
}

void	ft_creat_list(t_list **list, int fd)
{
	ssize_t	readbyte;
	char	*buffer;

	while (!ft_found_newligne(*list))
	{
		buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buffer)
			return ;
		readbyte = read(fd, buffer, BUFFER_SIZE);
		if (readbyte == 0 || readbyte == -1)
		{
			free(buffer);
			return ;
		}
		buffer[readbyte] = '\0';
		ft_connect_node(list, buffer);
	}
}

int	ft_lenline(t_list *list)
{
	int	i;
	int	len;

	len = 0;
	while (list)
	{
		i = 0;
		while (list -> buf[i])
		{
			if (list -> buf[i] == '\n')
			{
				len++;
				return (len);
			}
			len++;
			i++;
		}
		list = list -> next;
	}
	return (len);
}
