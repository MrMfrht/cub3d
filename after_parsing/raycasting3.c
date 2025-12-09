/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaher <fdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 11:56:00 by fdaher            #+#    #+#             */
/*   Updated: 2025/12/09 12:40:28 by fdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	check_texture_valid(t_image *tex, int x)
{
	if (!tex || !tex->img_data || tex->line_len <= 0 || tex->bpp <= 0)
	{
		printf("draw_wall_slice: missing texture data (x=%d)\n", x);
		return (0);
	}
	return (1);
}

static int	check_window_valid(t_image *win)
{
	if (!win || !win->img_data)
	{
		printf("draw_wall_slice: invalid window image\n");
		return (0);
	}
	return (1);
}

int	get_tex_color(t_image *tex, t_xy *pos)
{
	int		bytes_per_pixel;
	size_t	offset;
	size_t	buf_size;

	if (!tex || !tex->img_data || tex->line_len <= 0 || tex->bpp <= 0)
		return (-1);
	bytes_per_pixel = tex->bpp / 8;
	offset = (size_t)pos->y * (size_t)tex->line_len + (size_t)pos->x
		* (size_t)bytes_per_pixel;
	buf_size = (size_t)tex->height * (size_t)tex->line_len;
	if (offset + sizeof(int) > buf_size)
		return (-1);
	return (*(int *)(tex->img_data + offset));
}

static int	get_pixel_color(t_image *tex, t_ray *r, t_cub *cub, int y)
{
	t_xy	pos;
	int		tex_x;
	int		tex_y;

	tex_x = get_wall_tex_x(cub, r, tex);
	tex_y = (int)(((y - (-r->line_height / 2 + cub->window_image->height / 2))
				* tex->height) / r->line_height);
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= tex->height)
		tex_y = tex->height - 1;
	pos.x = tex_x;
	pos.y = tex_y;
	return (get_tex_color(tex, &pos));
}

// Draws the visible vertical wall stripe on screen
// 1- Select texture based on ray side/direction
// 2 - Compute X coordinate inside the texture
// 3 - Draw vertical pixels (from top to bottom)
void	draw_wall_slice(t_cub *cub, t_ray *r, int x)
{
	t_image	*tex;
	int		color;
	int		y;

	tex = select_texture(cub, r);
	if (!check_texture_valid(tex, x) || !cub
		|| !check_window_valid(cub->window_image))
		return ;
	y = r->draw_start;
	while (y < r->draw_end)
	{
		color = get_pixel_color(tex, r, cub, y);
		if (color < 0)
			break ;
		my_mlx_pixel_put(cub->window_image, x, y, color);
		y++;
	}
}
