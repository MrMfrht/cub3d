/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mofarhat <mofarhat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 13:28:46 by mofarhat          #+#    #+#             */
/*   Updated: 2025/10/19 15:30:56 by mofarhat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

char	**init_texture_path(t_cub *cub)
{
	char	**text_paths;

	text_paths = malloc(4 * sizeof(char *));
	text_paths[0] = cub->texture->no;
	text_paths[1] = cub->texture->so;
	text_paths[2] = cub->texture->we;
	text_paths[3] = cub->texture->ea;
	return (text_paths);
}

void	error_exit(t_cub *cub, char *s)
{
	free(cub);
	perror(s);
	exit(EXIT_FAILURE);
}

int	render_textures(t_cub *cub)
{
	int		i;
	char	**text_paths;

	text_paths = init_texture_path(cub);
	i = 0;
	while (i < 4)
	{
		cub->images[i].img_ptr = mlx_xpm_file_to_image(cub->mlx, text_paths[i],
				&cub->images[i].width, &cub->images[i].height);
		// ptr to the image in memory
		if (!cub->images[i].img_ptr)
			return (1);
		cub->images[i].img_data = mlx_get_data_addr(cub->images[i].img_ptr,
				&cub->images[i].bpp, &cub->images[i].line_len,
				&cub->images[i].endian);
		// ptr to the actual pixel data (raw bytes) of the image in memory
		if (!cub->images[i].img_data)
			return (1);
		i++;
	}
	return (0);
}

int	init_cub_images(t_cub *cub)
{
	int	i;

	cub->images = malloc(4 * sizeof(t_image));
	if (!cub->images)
		return (0);
	i = 0;
	while (i < 4)
	{
		cub->images[i].img_ptr = NULL;
		cub->images[i].img_data = NULL;
		cub->images[i].width = 0;
		cub->images[i].height = 0;
		cub->images[i].bpp = 0;
		cub->images[i].line_len = 0;
		cub->images[i].endian = 0;
		i++;
	}
	return (1);
}

t_cub	*init_cub(t_texture *node, t_map *map)
{
	t_cub	*cub;

	cub = malloc(sizeof(t_cub));
	cub->map = map;
	cub->texture = node;
	cub->mlx = NULL;
	cub->win = NULL;
	init_cub_images(cub);
	return (cub);
}

void	init_mlx(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		error_exit(cub, "Error\nmlx_init failed");
}

void draw_texture_debug(t_cub *cub)
{
	int i;
	t_image *image_tex;

	i = 0;
	while(i < 4)
	{
		image_tex = &cub->images[i];
		if(!image_tex->img_ptr)
			error_exit(cub,"Error: Missing texture image");
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

void	init_graphics(t_cub *cub)
{
	init_mlx(cub);
	if (!cub->mlx)
		error_exit(cub, "Error\nmlx_init failed");
	cub->win = mlx_new_window(cub->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "mofaCub");
	if (!cub->win)
		error_exit(cub, "Error\nWindow creation failed");
	cub->window_image->img_ptr = mlx_new_image(cub->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!cub->window_image->img_ptr)
		error_exit(cub, "Error\nImage buffer creation failed");
	cub->window_image->img_data = mlx_get_data_addr(cub->window_image->img_ptr, &cub->window_image->bpp, &cub->window_image->line_len,
			&cub->window_image->endian);
	if (!cub->window_image->img_data || cub->window_image->line_len <= 0 || cub->window_image->bpp <= 0)
		error_exit(cub, "Failed to get image data address");
	ft_memset(&cub->keys, 0, sizeof(t_keys));
	mlx_hook(cub->win, 17, 0, close_window, cub);
	mlx_hook(cub->win, 2, 1L << 0, handle_keypress, cub);
	mlx_hook(cub->win, 3, 1L << 1, handle_keyrelease, cub);
	draw_texture_debug(cub);
}

int	main(void)
{
	t_cub *cub;

	// Allocate and initialize cub structure
	cub = malloc(sizeof(t_cub));
	if (!cub)
	{
		perror("Error\nMalloc failed");
		return (1);
	}
	// Initialize all pointers to NULL
	cub->map = NULL;
	cub->texture = NULL;
	cub->mlx = NULL;
	cub->win = NULL;
	cub->images = NULL;

	// Initialize graphics (mlx and window)
	init_graphics(cub);

	// Start the event loop
	mlx_loop(cub->mlx);

	return (0);
}