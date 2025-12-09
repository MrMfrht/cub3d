/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaher <fdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 16:30:00 by fdaher            #+#    #+#             */
/*   Updated: 2025/12/09 16:53:07 by fdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3d.h"

static void	init_window_image(t_cub *cub)
{
	cub->window_image = malloc(sizeof(t_image));
	if (cub->window_image)
	{
		cub->window_image->width = SCREEN_WIDTH;
		cub->window_image->height = SCREEN_HEIGHT;
		cub->window_image->img_ptr = NULL;
		cub->window_image->img_data = NULL;
		cub->window_image->bpp = 0;
		cub->window_image->line_len = 0;
		cub->window_image->endian = 0;
	}
}

t_cub	*init_cub(t_texture *node, t_map *map)
{
	t_cub	*cub;

	cub = malloc(sizeof(t_cub));
	cub->map = map;
	cub->texture = node;
	cub->input = NULL;
	cub->mlx = NULL;
	cub->win = NULL;
	init_cub_images(cub);
	init_window_image(cub);
	cub->settings.move_speed = 0.08;
	cub->settings.rot_speed = 0.06;
	return (cub);
}
