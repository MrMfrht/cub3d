/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copilot <copilot@local>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 00:00:00 by copilot           #+#    #+#             */
/*   Updated: 2025/12/06 00:00:00 by copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
static int	is_cell_free(t_cub *cub, int iy, int ix)
{
    if (!cub || !cub->map)
        return (0);
    if (iy < 0 || iy >= cub->map->height || ix < 0 || ix >= cub->map->width)
        return (0);
    return (cub->map->map2d[iy][ix] != '1');
}

static void	move_axis_x(t_cub *cub, double new_x, double cur_y)
{
    int ix = (int)new_x;
    int iy = (int)cur_y;
    if (is_cell_free(cub, iy, ix))
        cub->player.x = new_x;
}

static void	move_axis_y(t_cub *cub, double new_y, double cur_x)
{
    int iy = (int)new_y;
    int ix = (int)cur_x;
    if (is_cell_free(cub, iy, ix))
        cub->player.y = new_y;
}

static void	move_along_vector(t_cub *cub, double vx, double vy, double speed)
{
    double cur_x = cub->player.x;
    double cur_y = cub->player.y;
    double new_x = cur_x + vx * speed;
    double new_y = cur_y + vy * speed;
    move_axis_x(cub, new_x, cur_y);
    move_axis_y(cub, new_y, cur_x);
}

static void	handle_rotation(t_cub *cub, double rot_speed)
{
    double rot = cub->keys.left ? -rot_speed : rot_speed;
    double old_dir_x = cub->player.dir_x;
    double old_plane_x = cub->player.plane_x;
    cub->player.dir_x = cub->player.dir_x * cos(rot) - cub->player.dir_y * sin(rot);
    cub->player.dir_y = old_dir_x * sin(rot) + cub->player.dir_y * cos(rot);
    cub->player.plane_x = cub->player.plane_x * cos(rot) - cub->player.plane_y * sin(rot);
    cub->player.plane_y = old_plane_x * sin(rot) + cub->player.plane_y * cos(rot);
}

void	update_player(t_cub *cub)
{
    double move_speed;
    double rot_speed;

    if (!cub || !cub->map || !cub->map->map2d)
        return ;
    /* read speeds from settings (defaults set in init_cub) */
    move_speed = cub->settings.move_speed;
    rot_speed = cub->settings.rot_speed;
    if (cub->keys.esc)
    {
        free_cub(cub);
        exit(0);
    }
    if (cub->keys.w)
        move_along_vector(cub, cub->player.dir_x, cub->player.dir_y, move_speed);
    if (cub->keys.s)
        move_along_vector(cub, -cub->player.dir_x, -cub->player.dir_y, move_speed);
    if (cub->keys.a)
        move_along_vector(cub, -cub->player.plane_x, -cub->player.plane_y, move_speed);
    if (cub->keys.d)
        move_along_vector(cub, cub->player.plane_x, cub->player.plane_y, move_speed);
    if (cub->keys.left || cub->keys.right)
        handle_rotation(cub, rot_speed);
}

