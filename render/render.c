#include "../cub3d.h"

int	render_scene(t_cub *cub)
{
	update_player(cub);

	draw_floor_ceiling(cub);
	ray_casting(cub);
	mlx_put_image_to_window(cub->mlx, cub->win,
		cub->window_image->img_ptr, 0, 0);
	return (0);
}
