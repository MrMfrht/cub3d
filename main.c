/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mofarhat <mofarhat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:31:13 by fdaher            #+#    #+#             */
/*   Updated: 2025/12/05 08:39:19 by mofarhat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_node_texture(t_texture *node)
{
	if (node->no)
		printf("no: %s\n", node->no);
	if (node->so)
		printf("so: %s\n", node->so);
	if (node->we)
		printf("we: %s\n", node->we);
	if (node->ea)
		printf("ea: %s\n", node->ea);
	if (node->f)
		printf("f=%d,%d,%d f_value=%d\n", node->f->red, node->f->green,
			node->f->blue, node->f->value);
	if (node->c)
		printf("c=%d,%d,%d c_value=%d\n", node->c->red, node->c->green,
			node->c->blue, node->c->value);
}

void	print_map(char **map)
{
	int		i;
	char	**temp;

	i = 0;
	if (!map)
		return ;
	temp = map;
	while (temp[i])
	{
		printf("->%s<-\n", temp[i]);
		i++;
	}
}

