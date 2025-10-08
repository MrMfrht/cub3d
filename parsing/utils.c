/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaher <fdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 11:01:31 by fdaher            #+#    #+#             */
/*   Updated: 2025/10/08 11:26:15 by fdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_all_texture(t_texture *node)
{
	if (!node)
		return (printf("Error\n we don't have texture_node"), -1);
	if (!(node->no))
		return (printf("Error\nplease put NO\n"), free_texture(node), -1);
	if (!(node->so))
		return (printf("Error\nplease put SO\n"), free_texture(node), -1);
	if (!(node->we))
		return (printf("Error\nplease put WE\n"), free_texture(node), -1);
	if (!(node->ea))
		return (printf("Error\nplease put EA\n"), free_texture(node), -1);
	if (!(node->f))
		return (printf("Error\nplease put F\n"), free_texture(node), -1);
	if (!(node->c))
		return (printf("Error\nplease put C\n"), free_texture(node), -1);
	return (0);
}
