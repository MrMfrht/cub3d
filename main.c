/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaher <fdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:31:13 by fdaher            #+#    #+#             */
/*   Updated: 2025/11/08 14:03:07 by fdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_node_texture(t_texture *node)
{
	if (node->no)
		printf("no: %s\n", node->no);
	if (node->so)
		printf("so: %s\n", node->so);
	if (node->we)
		printf("we: %s\n", node->we);
	if (node->ea)
		printf("ea: %s\n", node->ea);
	if (node->f)
		printf("f=%d,%d,%d\n", node->f->red, node->f->green, node->f->blue);
	if (node->c)
		printf("c=%d,%d,%d\n", node->c->red, node->c->green, node->c->blue);
}

void	print_map(char **map)
{
	int		i;
	char	**temp;

	i = 0;
	if (!map)
		return ;
	temp = map;
	while (temp[i])
	{
		printf("->%s<-\n", temp[i]);
		i++;
	}
}

// i modify 
int	free_cub(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	if (cub->window_image)
	{
		if (cub->window_image->img_ptr)
			mlx_destroy_image(cub->mlx, cub->window_image->img_ptr);
		free(cub->window_image);
	}
	if (cub->win)
		mlx_destroy_window(cub->mlx, cub->win);
	if (cub->mlx)
		free(cub->mlx);
	free(cub->texture);
	free(cub->map);
	free(cub);
	exit(0);
	return (0);
}

// i wanna test the ray_casting the main don't work

int	main(int argc, char **argv)
{
	char		**input;
	t_texture	*node_tex;
	t_map		*map;
	t_cub		*cub;

	if (argc != 2 || !argv[1] || check_cub(argv[1]) == 0)
		return (printf("Error\nUsage: ./cub3D <map.cub>\n"), 1);

	// 1️⃣ Read the map file into an array of strings
	input = read_from_file(argv[1]);
	if (!input)
		return (printf("Error\nFailed to read file\n"), 1);

	// 2️⃣ Initialize textures
	node_tex = create_texture();
	if (get_texture(input, node_tex) < 0)
		return (free_array(input), free_texture(node_tex), 1);

	// 3️⃣ Validate the map
	if (is_valid_map(input) < 0)
		return (free_array(input), free_texture(node_tex), 1);

	// 4️⃣ Initialize map and player
	map = init_map(input);
	cub = init_cub(node_tex, map);
	cub->player = init_player(map);

	// 5️⃣ Initialize MLX window and image
	init_mlx(cub);
	cub->window_image = malloc(sizeof(t_image));
	cub->window_image->img_ptr = mlx_new_image(cub->mlx,
			map->width * 64, map->height * 64);
	cub->window_image->img_data = mlx_get_data_addr(cub->window_image->img_ptr,
			&cub->window_image->bpp, &cub->window_image->line_len,
			&cub->window_image->endian);
	cub->window_image->width = map->width * 64;
	cub->window_image->height = map->height * 64;

	cub->win = mlx_new_window(cub->mlx, cub->window_image->width,
			cub->window_image->height, "cub3D Raycasting Test");

	// 6️⃣ Render the first frame (raycasting)
	draw_floor_ceiling(cub);
	ray_casting(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->window_image->img_ptr, 0, 0);

	// 7️⃣ Set hooks for keys and close
	mlx_hook(cub->win, 2, 1L << 0, handle_keypress, cub);
	mlx_hook(cub->win, 3, 1L << 1, handle_keyrelease, cub);
	mlx_hook(cub->win, 17, 0L, free_cub, cub); // close window

	// 8️⃣ Start the MLX loop
	mlx_loop(cub->mlx);

	// 9️⃣ Cleanup (never reached in MLX loop)
	free_tmap(map);
	free_array(input);
	free_texture(node_tex);
	return (0);
}


// int	main(int argc, char **argv)
// {
// 	char		**input;
// 	t_texture	*node_tex;
// 	t_map		*map;
// 	t_player	p;

// 	(void)argc;
// 	if (argc != 2 || argv[1][0] == '\0' || check_cub(argv[1]) == 0)
// 		return (printf("Error\nPut one argument of type \".cub\"\n"), 1);
// 	input = read_from_file(argv[1]);
// 	printf("hiiiiiiiiiiiiii input\n");
// 	node_tex = create_texture();
// 	if (get_texture(input, node_tex) < 0)
// 		return (free_array(input), 1);
// 	print_node_texture(node_tex);
// 	if (is_valid_map(input) < 0)
// 		return (free_array(input), free_texture(node_tex), 1);

// 	map = init_map(input);
// 	print_map(map->map2d);
// 	printf("heigth_map=%d and width_map=%d\n", map->height, map->width);
// 	p = init_player(map);
// 	printf("player: x=%f y=%f dir_x=%f dir_y=%f plane_x=%f plane_y=%f",
// 		p.x, p.y, p.dir_x, p.dir_y, p.plane_x, p.plane_y);
// 	free_tmap(map);
// 	free_array(input);
// 	free_texture(node_tex);
// 	return (0);
// }

// int	main(int argc, char **argv)
// {
// 	char		**input;
// 	t_texture	*node_tex;
// 	char		**rect_map;

// 	(void)argc;
// 	if (argc != 2 || argv[1][0] == '\0' || check_cub(argv[1]) == 0)
// 		return (printf("Error\nPut one argument of type \".cub\"\n"), 1);
// 	input = read_from_file(argv[1]);
// 	printf("hiiiiiiiiiiiiii input\n");
// 	node_tex = create_texture();
// 	if (get_texture(input, node_tex) < 0)
// 		return (free_array(input), 1);
// 	print_node_texture(node_tex);
// 	if (is_valid_map(input) < 0)
// 		return (free_array(input), free_texture(node_tex), 1);
// 	rect_map = get_rectangle_map(input);  //space to 1 and end_line to 1
// 	print_map(rect_map);
// 	free_array(rect_map);
// 	free_array(input);
// 	free_texture(node_tex);
// 	return (0);
// }
