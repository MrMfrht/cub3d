/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaher <fdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:46:01 by fdaher            #+#    #+#             */
/*   Updated: 2025/10/07 14:48:08 by fdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "./libft/libft.h"
# include "./minilibx-linux/mlx.h"
# include "get_next_line.h"
# include "minilibx-linux/mlx_int.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_color
{
	int			red;
	int			green;
	int			blue;
}	t_color;

typedef struct s_texture
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	t_color		*f;
	t_color		*c;
}				t_texture;

typedef struct s_cub
{
	char		**map;
	t_texture	*texture;
}				t_cub;

// ...........check.c---------------------------
int				check_cub(char *str);
int				check_xpm(char *str);
char			*ft_strndup(const char *start, size_t len);
t_texture		*create_texture(void);
void			free_texture(t_texture *node);
// ...........get_input.c------------------------
void			free_array(char **array);
char			**array_join(char **old_array, char *str_add);
char			**read_from_file(const char *s);
// ............get_texture.c----------------------
int				get_texture(char **array, t_texture *node);

#endif