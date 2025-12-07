/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mofarhat <mofarhat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 11:20:32 by fdaher            #+#    #+#             */
/*   Updated: 2025/12/05 18:03:24 by mofarhat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// -------------------- Free cub --------------------
void	free_cub(t_cub *cub)
{
	if (!cub)
		return ;
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
}
// -------------------- Error handler --------------------
void	error_exit(t_cub *cub, char *s)
{
	if (cub)
		free_cub(cub);
	perror(s);
	exit(EXIT_FAILURE);
}




// -------------------- Init MLX --------------------
int	init_mlx(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (-1);
	cub->win = mlx_new_window(cub->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	if (!cub->win)
		return (-1);
	cub->window_image = malloc(sizeof(t_image));
	if (!cub->window_image)
		return (-1);
	/* ensure width/height are initialized so draw loops run correctly */
	cub->window_image->width = SCREEN_WIDTH;
	cub->window_image->height = SCREEN_HEIGHT;
	cub->window_image->img_ptr = mlx_new_image(cub->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	cub->window_image->img_data = mlx_get_data_addr(cub->window_image->img_ptr,
		&cub->window_image->bpp,
		&cub->window_image->line_len,
		&cub->window_image->endian);
	return (0);
}

// -------------------- Render textures --------------------
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

// -------------------- Init cub --------------------
t_cub	*init_cub(t_texture *node, t_map *map)
{
	t_cub	*cub;

	cub = malloc(sizeof(t_cub));
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
	/* initialize key states to zero to avoid garbage values */
	cub->keys.w = 0;
	cub->keys.s = 0;
	cub->keys.a = 0;
	cub->keys.d = 0;
	cub->keys.left = 0;
	cub->keys.right = 0;
	cub->keys.esc = 0;
	return (cub);
}

// -------------------- Init graphics --------------------
void	init_graphics(t_cub *cub)
{
	init_mlx(cub);
	render_textures(cub);
}

// -------------------- Render scene --------------------
int	render_scene(t_cub *cub)
{
	/* Update player movement & rotation from key state */
	void	update_player(t_cub *cub)
	{
		double move_speed = 0.08; /* movement speed per frame */
		double rot_speed = 0.06;  /* rotation speed (radians) per frame */
		double new_x;
		double new_y;
		double cur_x;
		double cur_y;

		/* require valid map */
		if (!cub || !cub->map || !cub->map->map2d)
			return ;

		/* Exit on ESC */
		if (cub->keys.esc)
		{
			free_tmap(cub->map);
			free_cub(cub);
			exit(0);
		}

		/* Forward with per-axis collision (sliding) */
		cur_x = cub->player.x;
		cur_y = cub->player.y;
		if (cub->keys.w)
		{
			new_x = cur_x + cub->player.dir_x * move_speed;
			new_y = cur_y + cub->player.dir_y * move_speed;
			int ix_newx = (int)new_x;
			int iy_newy = (int)new_y;
			int ix_curx = (int)cur_x;
			int iy_cury = (int)cur_y;
			/* X axis check: can we move to new_x while staying in current row? */
			if (ix_newx >= 0 && ix_newx < cub->map->width && iy_cury >= 0 && iy_cury < cub->map->height
				&& cub->map->map2d[iy_cury][ix_newx] != '1')
				cub->player.x = new_x;
			/* Y axis check: can we move to new_y while staying in current column? */
			if (iy_newy >= 0 && iy_newy < cub->map->height && ix_curx >= 0 && ix_curx < cub->map->width
				&& cub->map->map2d[iy_newy][ix_curx] != '1')
				cub->player.y = new_y;
		}
		/* Backward with per-axis collision (sliding) */
		if (cub->keys.s)
		{
			new_x = cur_x - cub->player.dir_x * move_speed;
			new_y = cur_y - cub->player.dir_y * move_speed;
			int ix_newx = (int)new_x;
			int iy_newy = (int)new_y;
			int ix_curx = (int)cur_x;
			int iy_cury = (int)cur_y;
			if (ix_newx >= 0 && ix_newx < cub->map->width && iy_cury >= 0 && iy_cury < cub->map->height
				&& cub->map->map2d[iy_cury][ix_newx] != '1')
				cub->player.x = new_x;
			if (iy_newy >= 0 && iy_newy < cub->map->height && ix_curx >= 0 && ix_curx < cub->map->width
				&& cub->map->map2d[iy_newy][ix_curx] != '1')
				cub->player.y = new_y;
		}
		/* Strafe left with per-axis collision */
		if (cub->keys.a)
		{
			new_x = cur_x - cub->player.plane_x * move_speed;
			new_y = cur_y - cub->player.plane_y * move_speed;
			int ix_newx = (int)new_x;
			int iy_newy = (int)new_y;
			int ix_curx = (int)cur_x;
			int iy_cury = (int)cur_y;
			if (ix_newx >= 0 && ix_newx < cub->map->width && iy_cury >= 0 && iy_cury < cub->map->height
				&& cub->map->map2d[iy_cury][ix_newx] != '1')
				cub->player.x = new_x;
			if (iy_newy >= 0 && iy_newy < cub->map->height && ix_curx >= 0 && ix_curx < cub->map->width
				&& cub->map->map2d[iy_newy][ix_curx] != '1')
				cub->player.y = new_y;
		}
		/* Strafe right with per-axis collision */
		if (cub->keys.d)
		{
			new_x = cur_x + cub->player.plane_x * move_speed;
			new_y = cur_y + cub->player.plane_y * move_speed;
			int ix_newx = (int)new_x;
			int iy_newy = (int)new_y;
			int ix_curx = (int)cur_x;
			int iy_cury = (int)cur_y;
			if (ix_newx >= 0 && ix_newx < cub->map->width && iy_cury >= 0 && iy_cury < cub->map->height
				&& cub->map->map2d[iy_cury][ix_newx] != '1')
				cub->player.x = new_x;
			if (iy_newy >= 0 && iy_newy < cub->map->height && ix_curx >= 0 && ix_curx < cub->map->width
				&& cub->map->map2d[iy_newy][ix_curx] != '1')
				cub->player.y = new_y;
		}
		/* Rotation: left/right */
		if (cub->keys.left || cub->keys.right)
		{
			double rot = cub->keys.left ? -rot_speed : rot_speed;
			double old_dir_x = cub->player.dir_x;
			double old_plane_x = cub->player.plane_x;
			cub->player.dir_x = cub->player.dir_x * cos(rot) - cub->player.dir_y * sin(rot);
			cub->player.dir_y = old_dir_x * sin(rot) + cub->player.dir_y * cos(rot);
			cub->player.plane_x = cub->player.plane_x * cos(rot) - cub->player.plane_y * sin(rot);
			cub->player.plane_y = old_plane_x * sin(rot) + cub->player.plane_y * cos(rot);
		}
	}

	update_player(cub);

	draw_floor_ceiling(cub);
	ray_casting(cub);
	mlx_put_image_to_window(cub->mlx, cub->win,
		cub->window_image->img_ptr, 0, 0);
	return (0);
}

// -------------------- Main --------------------
int	main(int argc, char **argv)
{
	char		**input;
	t_texture	*node_tex;
	t_map		*map;
	t_cub		*cub;
	t_player	player;

	if (argc != 2)
		return (printf("Error\nUsage: ./cub3D map.cub\n"), 1);

	input = read_from_file(argv[1]);
	if (!input)
		return (printf("Error reading file\n"), 1);

	node_tex = create_texture();
	if (get_texture(input, node_tex) < 0)
		return (free_array(input), free_texture(node_tex), 1);

	if (is_valid_map(input) < 0)
		return (free_array(input), free_texture(node_tex), 1);

	map = init_map(input);
	player = init_player(map);

	cub = init_cub(node_tex, map);
	cub->player = player;

	init_graphics(cub);

	// Draw initial frame
	render_scene(cub);

	// Hooks
	mlx_hook(cub->win, 2, 1L << 0, handle_keypress, cub);
	mlx_hook(cub->win, 3, 1L << 1, handle_keyrelease, cub);
	mlx_loop_hook(cub->mlx, render_scene, cub);

	mlx_loop(cub->mlx);

	// Cleanup (never reached in typical MLX loop)
	free_tmap(map);
	free_array(input);
	free_texture(node_tex);
	free_cub(cub);

	return (0);
}
