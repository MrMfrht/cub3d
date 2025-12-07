/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mofarhat <mofarhat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:31:13 by fdaher            #+#    #+#             */
/*   Updated: 2025/12/05 08:39:19 by mofarhat         ###   ########.fr       */
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
		printf("f=%d,%d,%d f_value=%d\n", node->f->red, node->f->green,
			node->f->blue, node->f->value);
	if (node->c)
		printf("c=%d,%d,%d c_value=%d\n", node->c->red, node->c->green,
			node->c->blue, node->c->value);
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

// main moved from testing_main.c
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

