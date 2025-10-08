/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mofarhat <mofarhat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 13:28:46 by mofarhat          #+#    #+#             */
/*   Updated: 2025/10/08 12:29:45 by mofarhat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

char	**init_texture_path(t_cub *cub)
{
	char	**text_paths;

	text_paths = malloc(4 * sizeof(char *));
	text_paths[0] = cub->texture->no;
	text_paths[1] = cub->texture->so;
	text_paths[2] = cub->texture->we;
	text_paths[3] = cub->texture->ea;
	return (text_paths);
}

void	error_exit(t_game *game, char *s)
{
	free_cub(game);
	perror(s);
	exit(EXIT_FAILURE);
}

void init_cub_images(t_cub *cub)
{
	cub->images = malloc(4 * sizeof(t_image));
	if (!cub->images)
		return (1);
	int i = 0;
	while(i < 4)
	{
		cub->images.img_ptr = NULL;
		cub->images->img_data = NULL;
		cub->image->width = 0;
		cub->image->height = 0;
		cub->image->bpp = 0;
		cub->image->line_len = 0;
		cub->image->endian = 0;
		i++;
	}
}

t_cub	*init_cub(t_texture *node, t_map *map)
{
	t_cub *cub = malloc(sizeof(t_cub));
	cub->map = map;
	cub->texture = node;
	cub->mlx = NULL;
	cub->win = NULL;
	init_cub_images(t_cub);
}

int	init_mlx(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		error_exit_(cub, "Error\nmlx_init failed");
	return (0);
}

void	init_graphics(t_cub *cub)
{
	cub->mlx = init_mlx();
	if(!cub->mlx)
		error_exit(cub,"Error\nmlx_init failed");
	if (render_textures(cub))
		error_exit_(cub,"Error\nFailed to load textures");
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "mofaCub");
	if (!game->win)
		error_exit_(game, "Error\nWindow creation failed");
}


int	render_textures(t_cub *cub)
{
	int		i;
	char	**text_paths;

	text_paths = init_texture_path(cub);
	i = 0;
	while (i < 4)
	{
		cub->images[i].img_ptr = mlx_xpm_file_to_image(cub->mlx, text_paths[i],
				&cub->images[i].width, &cub->images[i].height); //ptr to the image in memory
		if (!cub->images[i].img_ptr)
			return (1);
		cub->images[i].img_data = mlx_get_data_addr(cub->images[i].img_ptr,
				&cub->images[i].bpp, &cub->images[i].line_len,
				&cub->images[i].endian); //ptr to the actual pixel data (raw bytes) of the image in memory
		if (!cub->images[i].img_data)
			return (1);
		i++;
	}
	return (0);
}

int main(void)
{
    t_cub cub;
    // ...initialize cub, textures, map, etc...
    init_graphics(&cub);
    mlx_loop(cub.mlx); // This keeps the window open
    return 0;
}