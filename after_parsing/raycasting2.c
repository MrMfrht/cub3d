/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaher <fdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 10:10:23 by fdaher            #+#    #+#             */
/*   Updated: 2025/11/08 14:04:00 by fdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// Correct the wall distance (perpendicular, not diagonal)
// Calculate projected line height based on distance
// Compute the vertical start and end of the wall slice
void	calculate_wall_distance(t_ray *r, t_player *p, t_cub *cub)
{
	if (r->side == 0)
		r->perp_wall_dist = (r->map_x - p->x
				+ (1 - r->step_x) / 2) / r->ray_dir_x;
	else
		r->perp_wall_dist = (r->map_y - p->y
				+ (1 - r->step_y) / 2) / r->ray_dir_y;
	r->line_height = (int)(cub->window_image->height / r->perp_wall_dist);
	r->draw_start = -r->line_height / 2 + cub->window_image->height / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->line_height / 2 + cub->window_image->height / 2;
	if (r->draw_end >= cub->window_image->height)
		r->draw_end = cub->window_image->height - 1;
}

// Choose the correct texture image based on wall side and ray direction
// 0:W 1:E 2:N 3:S
static t_image	*select_texture(t_cub *cub, t_ray *r)
{
	if (r->side == 0 && r->ray_dir_x < 0)
		return (&cub->images[0]);
	if (r->side == 0 && r->ray_dir_x > 0)
		return (&cub->images[1]);
	if (r->side == 1 && r->ray_dir_y < 0)
		return (&cub->images[2]);
	return (&cub->images[3]);
}

// Compute texture X coordinate (horizontal offset on texture)
// Find where the wall was hit (fractional part only)
// Scale wall_x (0–1) to texture width
static int	get_wall_tex_x(t_cub *cub, t_ray *r, t_image *tex)
{
	double	wall_x;
	int		tex_x;

	if (r->side == 0)
		wall_x = cub->player.y + r->perp_wall_dist * r->ray_dir_y;
	else
		wall_x = cub->player.x + r->perp_wall_dist * r->ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * tex->width);
	return (tex_x);
}

// Draws the visible vertical wall stripe on screen
// 1- Select texture based on ray side/direction
// 2 - Compute X coordinate inside the texture
// 3 - Draw vertical pixels (from top to bottom)
void	draw_wall_slice(t_cub *cub, t_ray *r, int x)
{
	t_image	*tex;
	int		tex_x;
	int		tex_y;
	int		y;
	int		color;

	tex = select_texture(cub, r);
	tex_x = get_wall_tex_x(cub, r, tex);
	y = r->draw_start;
	while (y < r->draw_end)
	{
		tex_y = (int)(((y - (-r->line_height / 2
							+ cub->window_image->height / 2))
					* tex->height) / r->line_height);
		color = *(int *)(tex->img_data + (tex_y * tex->line_len
					+ tex_x * (tex->bpp / 8)));
		my_mlx_pixel_put(cub->window_image, x, y, color);
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
// Perform raycasting to draw all wall columns
void	ray_casting(t_cub *cub)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < cub->window_image->width)
	{
		init_ray(&ray, cub, x);
		perform_dda(&ray, cub);
		calculate_wall_distance(&ray, &cub->player, cub);
		draw_wall_slice(cub, &ray, x);
		x++;
	}
}

// init_ray() → sets up ray direction & step sizes
// perform_dda() → loops until a wall is hit
// calculate_wall_height() → determines line height on screen
// draw_wall_slice() → actually draws pixels for that wall
