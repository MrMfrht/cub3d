/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaher <fdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 12:06:11 by fdaher            #+#    #+#             */
/*   Updated: 2025/12/09 11:20:27 by fdaher           ###   ########.fr       */
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

	if (!img || !img->img_data)
		return ;
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

// Initializes step direction (±1) and first side distances for DDA
static void	set_step_and_side_dist(t_ray *r, t_player *p)
{
	if (r->ray_dir_x < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (p->x - r->map_x) * r->delta_dist_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_x + 1.0 - p->x) * r->delta_dist_x;
	}
	if (r->ray_dir_y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (p->y - r->map_y) * r->delta_dist_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_y + 1.0 - p->y) * r->delta_dist_y;
	}
}

// Initialize a ray for a given column x
// fabs: function give the positive value of number
void	init_ray(t_ray *r, t_cub *cub, int x)
{
	r->camera_x = 2 * x / (double)cub->window_image->width - 1;
	r->ray_dir_x = cub->player.dir_x + cub->player.plane_x * r->camera_x;
	r->ray_dir_y = cub->player.dir_y + cub->player.plane_y * r->camera_x;
	r->map_x = (int)cub->player.x;
	r->map_y = (int)cub->player.y;
	r->delta_dist_x = fabs(1 / r->ray_dir_x);
	r->delta_dist_y = fabs(1 / r->ray_dir_y);
	r->hit = 0;
	set_step_and_side_dist(r, &cub->player);
}

// Digital Differential Analyzer (DDA):
// loop that moves the ray step by step until it hits a wall.
// was hit (vertical or horizontal) to handle texture direction later.
		// Check which side distance is smaller
		// Move to next square in x-direction or y-direction
		// 0 = hit a vertical wall
		// 1 = hit a horizontal wall
void	perform_dda(t_ray *r, t_cub *cub)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->delta_dist_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_dist_y += r->delta_dist_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (r->map_x < 0 || r->map_x >= cub->map->width
			|| r->map_y < 0 || r->map_y >= cub->map->height
			|| cub->map->map2d[r->map_y][r->map_x] == '1')
			hit = 1;
	}
}
