/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaher <fdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:46:01 by fdaher            #+#    #+#             */
/*   Updated: 2025/12/09 16:53:07 by fdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "./libft/libft.h"
# include "./minilibx-linux/mlx.h"
# include "./minilibx-linux/mlx_int.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define SCREEN_WIDTH 800  // 1920
# define SCREEN_HEIGHT 700 // Structs		//1080
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

typedef struct s_dim
{
	int			width;
	int			height;
}				t_dim;

// img_ptr:pointer to image in MLX
// img_data:pointer to pixel memory (raw bytes)
// bpp:bits per pixel (usually 32)
// line_len:number of bytes in a single row
// endian:0 = little endian, 1 = big endian
// endian:tells how pixel color data is stored in memory.

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
	int			value;
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

typedef struct s_settings
{
	double		move_speed;
	double		rot_speed;
}				t_settings;

typedef struct s_cub
{
	t_map		*map;
	t_texture	*texture;
	char		**input;
	void		*mlx;
	void		*win;
	t_image		*images;
	t_image		*window_image;
	t_settings	settings;
	t_keys		keys;
	t_player	player;
}				t_cub;

typedef struct s_xy
{
	int		x;
	int		y;
}	t_xy;

// camera_x;    X-coordinate on camera plane (-1 to 1)
// ray_dir_x;  Ray direction vector X
// ray_dir_y;  Ray direction vector Y
// map_x;  Current grid square X in the map
// map_y; Current grid square Y in the map
// side_dist_x;  Distance to next x-side
// side_dist_y;  Distance to next y-side
// delta_dist_x; Distance between x-side crossings
// delta_dist_y; Distance between y-side crossings
// perp_wall_dist; (perpendicular) wall distance
// step_x;  Step direction in x (+1 or -1)
// step_y; Step direction in y (+1 or -1)
// hit;  Becomes 1 when a wall is hit
// side; 0 if hit x-side, 1 if y-side
// line_height; Projected wall height on screen
// draw_start; Top pixel of the wall on screen
// draw_end; Bottom pixel of the wall on screen

typedef struct s_ray
{
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
}				t_ray;

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
int				is_border_valid(char *line);
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
int				map_max_width(char **map);
int				map_height(char **map);
char			*pad_line_with_spaces(char *line, int max_map_width);
void			pad_map_with_spaces(char **map);
int				is_valid_char(char c);
int				is_player_char(char c);
int				validate_characters_and_player(char **map);
char			**duplicate_map(char **map);
void			free_map(char **map);
int				find_player_position(char **map, int *x, int *y);
int				validate_map(char **map);

/////////////////////////////////////render
t_cub			*init_cub(t_texture *node, t_map *map);
int				init_cub_images(t_cub *cub);
void			init_mlx(t_cub *cub);
void			init_graphics(t_cub *cub);
void			error_exit(t_cub *cub, char *s);
int				render_textures(t_cub *cub);
void			draw_texture_debug(t_cub *cub);

void			free_cub(t_cub *cub);
int				close_window(t_cub *cub);
int				handle_keyrelease(int keycode, t_cub *cub);
int				handle_keypress(int keycode, t_cub *cub);

void			update_player(t_cub *cub);
int				render_scene(t_cub *cub);

/////////////////////////////////////after_parsing
// ............init_map_player.c
int				height_of_map(char **map);
t_map			*init_map(char **input);
void			free_tmap(t_map *map);
t_player		init_player(t_map *map);
// .............raycasting1.c
void			my_mlx_pixel_put(t_image *img, int x, int y, int color);
void			draw_floor_ceiling(t_cub *cub);
void			init_ray(t_ray *r, t_cub *cub, int x);
void			perform_dda(t_ray *r, t_cub *cub);
// .............raycasting2.c
void			calculate_wall_distance(t_ray *r, t_player *p, t_cub *cub);
t_image			*select_texture(t_cub *cub, t_ray *r);
int				get_wall_tex_x(t_cub *cub, t_ray *r, t_image *tex);
void			ray_casting(t_cub *cub);
// .............raycasting3.c
void			draw_wall_slice(t_cub *cub, t_ray *r, int x);

// main.c

#endif