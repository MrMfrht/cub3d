/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaher <fdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:46:01 by fdaher            #+#    #+#             */
/*   Updated: 2025/10/21 14:53:48 by fdaher           ###   ########.fr       */
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

# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 700 // Structs
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define MAX_KEYS 256
# define KEY_ESC 65307

typedef struct s_map
{
	char		**map2d;
	int			width;
	int			height;
}				t_map;

typedef struct s_image
{
	void		*img_ptr;
	char		*img_data;
	int			width;
	int			height;
	int			bpp;
	int			line_len;
	int			endian;
}				t_image;

typedef struct s_color
{
	int			red;
	int			green;
	int			blue;
	int			value;					// i want use a function "<<"
}				t_color;

typedef struct s_texture
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	t_color		*f;
	t_color		*c;
}				t_texture;

typedef struct s_keys
{
	int			w;
	int			s;
	int			a;
	int			d;
	int			left;
	int			right;
	int			esc;
}				t_keys;

typedef struct s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_player;

typedef struct s_cub
{
	t_map		*map;
	t_texture	*texture;
	void		*mlx;
	void		*win;
	t_image		*images;
	t_image		*window_image;
	t_keys		keys;
	t_player	player;
}				t_cub;

/////////////////////////////////////parsing
// ...........check.c---------------------------
int				check_cub(char *str);
int				check_xpm(char *str);
char			*ft_strndup(const char *start, size_t len);
t_texture		*create_texture(void);
void			free_texture(t_texture *node);
//.............utils.c----------------------------
int				check_all_texture(t_texture *node);
int				is_valid_map(char **input);
int				find_map_start(char **input);
// ...........get_input.c------------------------
void			free_array(char **array);
char			**array_join(char **old_array, char *str_add);
char			**read_from_file(const char *s);
// ............get_texture.c----------------------
int				get_texture(char **array, t_texture *node);
// ............get_map.c--------------------------
char			**get_map(char **input);
// ............get_rectangle.c--------------------------
char			**get_rectangle_map(char **input);
// ............validation
int				validate_map(char **map);
void			free_cub(t_cub *cub);
int				handle_keyrelease(int keycode, t_cub *cub);
int				handle_keypress(int keycode, t_cub *cub);

#endif