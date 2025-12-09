/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaher <fdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 13:28:46 by mofarhat          #+#    #+#             */
/*   Updated: 2025/12/09 16:28:08 by fdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3d.h"

char	**init_texture_path(t_cub *cub)
{
	char	**text_paths;

	text_paths = malloc(4 * sizeof(char *));
	text_paths[0] = cub->texture->we;
	text_paths[1] = cub->texture->ea;
	text_paths[2] = cub->texture->no;
	text_paths[3] = cub->texture->so;
	return (text_paths);
}

void	error_exit(t_cub *cub, char *s)
{
	free(cub);
	perror(s);
	exit(EXIT_FAILURE);
}

static int	load_single_texture(t_cub *cub, int i, char *path)
{
	cub->images[i].img_ptr = mlx_xpm_file_to_image(cub->mlx, path,
			&cub->images[i].width, &cub->images[i].height);
	if (!cub->images[i].img_ptr)
		return (1);
	cub->images[i].img_data = mlx_get_data_addr(cub->images[i].img_ptr,
			&cub->images[i].bpp, &cub->images[i].line_len,
			&cub->images[i].endian);
	if (!cub->images[i].img_data)
		return (1);
	return (0);
}

int	render_textures(t_cub *cub)
{
	int		i;
	char	**text_paths;

	text_paths = init_texture_path(cub);
	i = 0;
	while (i < 4)
	{
		if (load_single_texture(cub, i, text_paths[i]))
		{
			free(text_paths);
			return (1);
		}
		i++;
	}
	free(text_paths);
	return (0);
}

static void	init_single_image(t_image *img)
{
	img->img_ptr = NULL;
	img->img_data = NULL;
	img->width = 0;
	img->height = 0;
	img->bpp = 0;
	img->line_len = 0;
	img->endian = 0;
}

int	init_cub_images(t_cub *cub)
{
	int	i;

	cub->images = malloc(4 * sizeof(t_image));
	if (!cub->images)
		return (0);
	i = 0;
	while (i < 4)
	{
		init_single_image(&cub->images[i]);
		i++;
	}
	return (1);
}
