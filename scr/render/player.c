/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaher <fdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 00:00:00 by fdaher            #+#    #+#             */
/*   Updated: 2025/12/09 17:36:07 by fdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	is_cell_free(t_cub *cub, int iy, int ix)
{
	if (!cub || !cub->map)
		return (0);
	if (iy < 0 || iy >= cub->map->height || ix < 0 || ix >= cub->map->width)
		return (0);
	return (cub->map->map2d[iy][ix] != '1');
}

static void	move_along_vector(t_cub *cub, double vx, double vy, double speed)
{
	double	cur_x;
	double	cur_y;
	double	new_x;
	double	new_y;

	cur_x = cub->player.x;
	cur_y = cub->player.y;
	new_x = cur_x + vx * speed;
	new_y = cur_y + vy * speed;
	if (is_cell_free(cub, (int)cur_y, (int)new_x))
		cub->player.x = new_x;
	if (is_cell_free(cub, (int)new_y, (int)cur_x))
		cub->player.y = new_y;
}

static void	handle_rotation(t_cub *cub, double rot_speed)
{
	double	rot;
	double	old_dir_x;
	double	old_plane_x;

	if (cub->keys.left)
		rot = -rot_speed;
	else
		rot = rot_speed;
	old_dir_x = cub->player.dir_x;
	old_plane_x = cub->player.plane_x;
	cub->player.dir_x = cub->player.dir_x * cos(rot)
		- cub->player.dir_y * sin(rot);
	cub->player.dir_y = old_dir_x * sin(rot) + cub->player.dir_y * cos(rot);
	cub->player.plane_x = cub->player.plane_x * cos(rot)
		- cub->player.plane_y * sin(rot);
	cub->player.plane_y = old_plane_x * sin(rot)
		+ cub->player.plane_y * cos(rot);
}

static void	handle_movement(t_cub *cub, double move_speed)
{
	if (cub->keys.w)
		move_along_vector(cub, cub->player.dir_x,
			cub->player.dir_y, move_speed);
	if (cub->keys.s)
		move_along_vector(cub, -cub->player.dir_x, -cub->player.dir_y,
			move_speed);
	if (cub->keys.a)
		move_along_vector(cub, -cub->player.plane_x, -cub->player.plane_y,
			move_speed);
	if (cub->keys.d)
		move_along_vector(cub, cub->player.plane_x, cub->player.plane_y,
			move_speed);
}

void	update_player(t_cub *cub)
{
	double	move_speed;
	double	rot_speed;

	if (!cub || !cub->map || !cub->map->map2d)
		return ;
	move_speed = cub->settings.move_speed;
	rot_speed = cub->settings.rot_speed;
	if (cub->keys.esc)
	{
		free_cub(cub);
		exit(0);
	}
	handle_movement(cub, move_speed);
	if (cub->keys.left || cub->keys.right)
		handle_rotation(cub, rot_speed);
}
