/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaher <fdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 10:42:19 by fdaher            #+#    #+#             */
/*   Updated: 2025/11/11 11:47:28 by fdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
// -------------------- Free cub --------------------
int	free_cub(t_cub *cub)
{
	if (!cub)
		return (0);
	if (cub->images)
	{
		for (int i = 0; i < 4; i++)
			if (cub->images[i].img_ptr)
				mlx_destroy_image(cub->mlx, cub->images[i].img_ptr);
		free(cub->images);
	}
	if (cub->window_image && cub->window_image->img_ptr)
		mlx_destroy_image(cub->mlx, cub->window_image->img_ptr);
	if (cub->win)
		mlx_destroy_window(cub->mlx, cub->win);
	if (cub->mlx)
		cub->mlx = NULL;
	free(cub);
	return (0);
}

void	error_exit(t_cub *cub, char *s)
{
	if (cub)
		free_cub(cub);
	perror(s);
	exit(EXIT_FAILURE);
}

// Minimal init MLX
int	init_mlx(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (-1);
	cub->win = mlx_new_window(cub->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D Test");
	if (!cub->win)
		return (-1);
	cub->window_image = malloc(sizeof(t_image));
	if (!cub->window_image)
		return (-1);
	cub->window_image->img_ptr = mlx_new_image(cub->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	cub->window_image->img_data = mlx_get_data_addr(
		cub->window_image->img_ptr,
		&cub->window_image->bpp,
		&cub->window_image->line_len,
		&cub->window_image->endian
	);
	return (0);
}

// Minimal render textures (assumes cub->images[0..3] exist)
void	render_textures(t_cub *cub)
{
	for (int i = 0; i < 4; i++)
	{
		cub->images[i].img_ptr = mlx_xpm_file_to_image(cub->mlx,
			(i == 0) ? cub->texture->we :
			(i == 1) ? cub->texture->ea :
			(i == 2) ? cub->texture->no :
			cub->texture->so,
			&cub->images[i].width, &cub->images[i].height);
		if (!cub->images[i].img_ptr)
			error_exit(cub, "Failed to load texture");
		cub->images[i].img_data = mlx_get_data_addr(cub->images[i].img_ptr,
			&cub->images[i].bpp,
			&cub->images[i].line_len,
			&cub->images[i].endian);
	}
}

// Minimal init cub structure
t_cub	*init_cub(t_texture *node, t_map *map, t_player player)
{
	t_cub	*cub = malloc(sizeof(t_cub));
	if (!cub)
		return (NULL);

	cub->map = map;
	cub->texture = node;
	cub->images = malloc(4 * sizeof(t_image));
	if (!cub->images)
		return (free(cub), NULL);
	for (int i = 0; i < 4; i++)
	{
		cub->images[i].img_ptr = NULL;
		cub->images[i].img_data = NULL;
	}
	cub->window_image = NULL;
	cub->mlx = NULL;
	cub->win = NULL;
	cub->player = player;
	return cub;
}

// Render scene: draw floor, ceiling and walls
int	render_scene(t_cub *cub)
{
	draw_floor_ceiling(cub);
	ray_casting(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->window_image->img_ptr, 0, 0);
	return (0);
}



int	main(int argc, char **argv)
{
	t_cub		*cub;
	char		**input;
	t_texture	*node_tex;
	t_map		*map;
	t_player	player;

	if (argc != 2)
		return (printf("ERROR\nUsage: %s map.cub\n", argv[0]), 0);

	// Read input file
	input = read_from_file(argv[1]);
	if (!input)
		return (printf("ERROR\nCannot read map file\n"), 0);

	// Create texture structure and parse textures
	node_tex = create_texture();
	if (get_texture(input, node_tex) < 0)
		return (free_array(input), free_texture(node_tex), 0);

	// Validate map
	if (is_valid_map(input) < 0)
		return (free_array(input), free_texture(node_tex), 0);

	// Initialize map and player
	map = init_map(input);
	player = init_player(map);

	// Initialize cub structure
	cub = init_cub(node_tex, map, player);

	// Initialize MLX, window, and textures
	if (init_mlx(cub) < 0)
		error_exit(cub, "Failed to initialize MLX");
	render_textures(cub);

	// Draw initial frame (floor, ceiling, walls)
	render_scene(cub);

	// Hook close window
	mlx_hook(cub->win, 17, 0, free_cub, cub);

	// Set render loop (for future animation / movement)
	mlx_loop_hook(cub->mlx, render_scene, cub);
	mlx_loop(cub->mlx);

	// Cleanup
	free_tmap(map);
	free_array(input);
	free_texture(node_tex);

	return (0);
}

// ------------------------ MAIN ------------------------
// int	main(int argc, char **argv)
// {
// 	char		**input;
// 	t_texture	*node_tex;
// 	t_map		*map;
// 	t_player	player;
// 	t_cub		*cub;

// 	if (argc != 2)
// 		return (printf("Error\nUsage: ./cub3D map.cub\n"), 1);

// 	input = read_from_file(argv[1]);
// 	if (!input)
// 		return (printf("Error reading file\n"), 1);

// 	node_tex = create_texture();
// 	if (get_texture(input, node_tex) < 0)
// 		return (free_array(input), free_texture(node_tex), 1);

// 	if (is_valid_map(input) < 0)
// 		return (free_array(input), free_texture(node_tex), 1);

// 	map = init_map(input);
// 	player = init_player(map);  // Initialize player position and direction

// 	cub = init_cub(node_tex, map, player);

// 	// Initialize MLX, window and textures
// 	if (init_mlx(cub) < 0)
// 		error_exit(cub, "Failed to initialize MLX");
// 	render_textures(cub);

// 	// Draw 3D scene once
// 	render_scene(cub);

// 	// Wait for user to close window (no movement handling)
// 	mlx_hook(cub->win, 17, 0, free_cub, cub); // close window
// 	mlx_loop(cub->mlx);

// 	return (0);
// }
