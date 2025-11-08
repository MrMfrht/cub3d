/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaher <fdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 13:42:02 by mofarhat          #+#    #+#             */
/*   Updated: 2025/11/08 13:40:40 by fdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	if (map->map2d)
	{
		i = 0;
		while (i < map->height && map->map2d[i])
		{
			free(map->map2d[i]);
			i++;
		}
		free(map->map2d);
	}
	free(map);
}

static void	free_texture_paths(t_texture *texture)
{
	if (texture->no)
		free(texture->no);
	if (texture->so)
		free(texture->so);
	if (texture->we)
		free(texture->we);
	if (texture->ea)
		free(texture->ea);
}

void	free_texture(t_texture *texture)
{
	if (!texture)
		return ;
	free_texture_paths(texture);
	if (texture->f)
		free(texture->f);
	if (texture->c)
		free(texture->c);
	free(texture);
}

void	free_image(void *mlx, t_image *image)
{
	if (!image)
		return ;
	if (image->img_ptr && mlx)
		mlx_destroy_image(mlx, image->img_ptr);
	free(image);
}

void	free_images_array(void *mlx, t_image *images, int count)
{
	int	i;

	if (!images)
		return ;
	i = 0;
	while (i < count)
	{
		if (images[i].img_ptr && mlx)
			mlx_destroy_image(mlx, images[i].img_ptr);
		i++;
	}
	free(images);
}

static void	free_cub_resources(t_cub *cub)
{
	if (cub->map)
		free_map(cub->map);
	if (cub->texture)
		free_texture(cub->texture);
	if (cub->images)
		free_images_array(cub->mlx, cub->images, 4);
	if (cub->window_image)
		free_image(cub->mlx, cub->window_image);
}

// void	free_cub(t_cub *cub)
// {
// 	if (!cub)
// 		return ;
// 	free_cub_resources(cub);
// 	if (cub->win && cub->mlx)
// 		mlx_destroy_window(cub->mlx, cub->win);
// 	if (cub->mlx)
// 	{
// 		mlx_destroy_display(cub->mlx);
// 		free(cub->mlx);
// 	}
// 	free(cub);
// }


