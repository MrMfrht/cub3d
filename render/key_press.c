/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaher <fdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 15:08:28 by mofarhat          #+#    #+#             */
/*   Updated: 2025/11/11 11:57:41 by fdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	handle_keypress(int keycode, t_cub *cub)
{
	if (keycode == KEY_ESC)
		close_window(cub);
	else if (keycode == KEY_W)
		cub->keys.w = 1;
	else if (keycode == KEY_S)
		cub->keys.s = 1;
	else if (keycode == KEY_A)
		cub->keys.a = 1;
	else if (keycode == KEY_D)
		cub->keys.d = 1;
	else if (keycode == KEY_LEFT)
		cub->keys.left = 1;
	else if (keycode == KEY_RIGHT)
		cub->keys.right = 1;
	return (0);
}

int	handle_keyrelease(int keycode, t_cub *cub)
{
	if (keycode == KEY_ESC)
		cub->keys.esc = 0;
	else if (keycode == KEY_W)
		cub->keys.w = 0;
	else if (keycode == KEY_S)
		cub->keys.s = 0;
	else if (keycode == KEY_A)
		cub->keys.a = 0;
	else if (keycode == KEY_D)
		cub->keys.d = 0;
	else if (keycode == KEY_LEFT)
		cub->keys.left = 0;
	else if (keycode == KEY_RIGHT)
		cub->keys.right = 0;
	printf("postion at x:%f ,y: %f\n", cub->player.x, cub->player.y);
	return (0);
}
