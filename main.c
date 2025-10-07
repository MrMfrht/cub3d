/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaher <fdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:31:13 by fdaher            #+#    #+#             */
/*   Updated: 2025/10/07 15:07:15 by fdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_node_texture(t_texture *node)
{
	if (node->no)
		printf("no: %s\n", node->no);
	if (node->so)
		printf("no: %s\n", node->so);
	if (node->we)
		printf("no: %s\n", node->we);
	if (node->ea)
		printf("no: %s\n", node->ea);
	if (node->f)
		printf("f=%d,%d,%d\n", node->f->red, node->f->green, node->f->blue);
	if (node->c)
		printf("f=%d,%d,%d\n", node->c->red, node->c->green, node->c->blue);
}

int	main(int argc, char **argv)
{
	char		**input;
	t_texture	*node_tex;

	(void)argc;
	if (argc != 2 || argv[1][0] == '\0' || check_cub(argv[1]) == 0)
		return (1);
	input = read_from_file(argv[1]);
	printf("hiiiiiiiiiiiiii input");
	node_tex = create_texture();
	if (get_texture(input, node_tex) < 0)
		return(free_array(input), 1);
	print_node_texture(node_tex);
	free_array(input);
	free_texture(node_tex);
	return (0);
}
// int	main(int argc, char **argv)
// {
//     char **input;
//     t_texture   *node_tex;
//     t_cub *cub;
// 	if (argc != 2 || argv[1][0] == '\0' || check_ber(argv[1]) == 0)
// 		return (1);
// 	//get__input (the input "___.cub")
// 	//check_line_of_map (if it conmposed of only 6 caracter)
// 	//get_path_map (get NO, SO, WE, EA, F AND THE MAP_without_space)
// 	//check_map(same width, closed by 1)
// 	// !! start the game in case valide mape

// 	return (0);
// }
