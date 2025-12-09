/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaher <fdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 12:10:44 by fdaher            #+#    #+#             */
/*   Updated: 2025/12/09 16:25:42 by fdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	height_of_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

//init the map node
t_map	*init_map(char **input)
{
	t_map	*node_map;

	node_map = (t_map *)malloc(sizeof(t_map));
	if (!node_map)
		return (printf("Error! malloc t_map (in init_map)\n"), NULL);
	node_map->map2d = get_rectangle_map(input);
	node_map->width = ft_strlen(node_map->map2d[0]);
	node_map->height = height_of_map(node_map->map2d);
	return (node_map);
}

// free the map node
void	free_tmap(t_map *map)
{
	if (!map)
		return ;
	if (map->map2d)
		free_array(map->map2d);
	if (map)
		free(map);
}

// direction_player N(0;-1) S(0;1) w(-1;0) E(1;0)
// plane_xy Camera plane (perpendicular to direction)
// plane_x = -dir_y * 0.66
// plane_y = dir_x * 0.66
// plane = perpendicular(dir) × 0.66
static void	set_dir_plane(t_player *p, char c)
{
	if (c == 'N')
	{
		p->dir_x = 0;
		p->dir_y = -1;
	}
	else if (c == 'S')
	{
		p->dir_x = 0;
		p->dir_y = 1;
	}
	else if (c == 'E')
	{
		p->dir_x = 1;
		p->dir_y = 0;
	}
	else if (c == 'W')
	{
		p->dir_x = -1;
		p->dir_y = 0;
	}
	p->plane_x = -p->dir_y * 0.66;
	p->plane_y = p->dir_x * 0.66;
}

// get the position of player
// +0.5:We center player inside the map square, rays don’t start on a grid edge
t_player	init_player(t_map *map)
{
	t_player	p;
	int			x;
	int			y;

	if (!find_player_position(map->map2d, &x, &y))
	{
		printf("Error!player not found (in init_player)\n");
		free_tmap(map);
		exit(1);
	}
	p.x = x + 0.5;
	p.y = y + 0.5;
	set_dir_plane(&p, map->map2d[y][x]);
	map->map2d[y][x] = '0';
	return (p);
}
