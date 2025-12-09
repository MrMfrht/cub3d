/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaher <fdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 16:30:00 by fdaher            #+#    #+#             */
/*   Updated: 2025/12/09 16:53:07 by fdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3d.h"

void	init_mlx(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		error_exit(cub, "Error\nmlx_init failed");
}

void	draw_texture_debug(t_cub *cub)
{
	int		i;
	t_image	*image_tex;

	i = 0;
	while (i < 4)
	{
		image_tex = &cub->images[i];
		if (!image_tex->img_ptr)
			error_exit(cub, "Error: Missing texture image");
		mlx_put_image_to_window(cub->mlx, cub->win, image_tex->img_ptr, (i % 2)
			* image_tex->width, (i / 2) * image_tex->height);
		i++;
	}
}

int	close_window(t_cub *cub)
{
	if (cub->window_image->img_ptr)
		free_cub(cub);
	exit(0);
}

static void	init_graphics_hooks(t_cub *cub)
{
	ft_memset(&cub->keys, 0, sizeof(t_keys));
	mlx_hook(cub->win, 17, 0, close_window, cub);
	mlx_hook(cub->win, 2, 1L << 0, handle_keypress, cub);
	mlx_hook(cub->win, 3, 1L << 1, handle_keyrelease, cub);
	if (render_textures(cub))
		error_exit(cub, "Error: Failed to load texture images");
	draw_texture_debug(cub);
}

void	init_graphics(t_cub *cub)
{
	init_mlx(cub);
	if (!cub->mlx)
		error_exit(cub, "Error\nmlx_init failed");
	cub->win = mlx_new_window(cub->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
	if (!cub->win)
		error_exit(cub, "Error\nWindow creation failed");
	cub->window_image->img_ptr = mlx_new_image(cub->mlx, SCREEN_WIDTH,
			SCREEN_HEIGHT);
	if (!cub->window_image->img_ptr)
		error_exit(cub, "Error\nImage buffer creation failed");
	cub->window_image->img_data = mlx_get_data_addr(cub->window_image->img_ptr,
			&cub->window_image->bpp, &cub->window_image->line_len,
			&cub->window_image->endian);
	if (!cub->window_image->img_data || cub->window_image->line_len <= 0
		|| cub->window_image->bpp <= 0)
		error_exit(cub, "Failed to get image data address");
	init_graphics_hooks(cub);
}
