/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaher <fdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 10:10:23 by fdaher            #+#    #+#             */
/*   Updated: 2025/12/09 12:53:18 by fdaher           ###   ########.fr       */
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
t_image	*select_texture(t_cub *cub, t_ray *r)
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
int	get_wall_tex_x(t_cub *cub, t_ray *r, t_image *tex)
{
	double	wall_x;
	int		tex_x;

	if (r->side == 0)
		wall_x = cub->player.y + r->perp_wall_dist * r->ray_dir_y;
	else
		wall_x = cub->player.x + r->perp_wall_dist * r->ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * tex->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	return (tex_x);
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
