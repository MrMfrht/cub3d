/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaher <fdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:31:13 by fdaher            #+#    #+#             */
/*   Updated: 2025/11/11 11:54:02 by fdaher           ###   ########.fr       */
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


//  check init_player

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

//check get_rectangle

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
