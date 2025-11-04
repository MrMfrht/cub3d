/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaher <fdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 12:06:11 by fdaher            #+#    #+#             */
/*   Updated: 2025/11/04 12:47:08 by fdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// Each pixel = (y * bytes_per_line) + (x * bytes_per_pixel)
// Each row in memory has line_len bytes.
// Each pixel takes bpp / 8 bytes.
// So we compute the offset and write the color "c and f".
void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return ;
	dst = img->img_data + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

//  heigth / 2 for put ceiling and flor
//	Upper half = ceiling color, lower half = ceiling color
void	draw_floor_ceiling(t_cub *cub)
{
	int	y;
	int	x;
	int	color_c;
	int	color_f;

	color_c = cub->texture->c->value;
	color_f = cub->texture->f->value;
	y = 0;
	while (y < cub->window_image->height)
	{
		x = 0;
		while (x < cub->window_image->width)
		{
			if (y < cub->window_image->height / 2)
				my_mlx_pixel_put(cub->window_image, x, y, color_c);
			else
				my_mlx_pixel_put(cub->window_image, x, y, color_f);
			x++;
		}
		y++;
	}
}

// For each vertical line (x) on your screen:
// 1-Cast a ray from the player.
// 2-Find where it hits a wall in the map.
// 3-Compute distance to the wall.
// 4-Calculate line height to draw that wall slice.
// 5-Choose correct texture (N/S/E/W).
// 6-Draw the textured wall column.
void	raycast(t_cub *cub)
{
	int	x;

	x = 0;
	while (x < cub->window_image->width)
	{
		cast_ray(cub, x);
		x++;
	}
}










// init_ray() → sets up ray direction & step sizes

// perform_dda() → loops until a wall is hit

// calculate_wall_height() → determines line height on screen

// draw_wall_slice() → actually draws pixels for that wall