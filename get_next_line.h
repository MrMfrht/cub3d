/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaher <fdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:58:16 by fdaher            #+#    #+#             */
/*   Updated: 2025/10/03 14:27:12 by fdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	char			*buf;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
t_list	*ft_last_node(t_list *list);
int		ft_found_newligne(t_list *list);
void	ft_connect_node(t_list	**list, char *buffer);
void	ft_creat_list(t_list **list, int fd);
int		ft_lenline(t_list *list);
void	ft_copy(t_list *list, char *s);
char	*ft_get_line(t_list *list);
void	ft_reste_node(t_list **list);
void	free_every_node(t_list **list, t_list *rest_node, char *buffer);

#endif