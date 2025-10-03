/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaher <fdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:46:01 by fdaher            #+#    #+#             */
/*   Updated: 2025/10/03 14:29:13 by fdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include "get_next_line.h"
# include "./libft/libft.h"
# include "./minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"
# include "get_next_line.h"

typedef struct s_texture
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*f;
	char	*c;
}	t_texture;

// ...........check.c
int		check_cub(char *str);
int		check_xpm(char *str);
char	*ft_strndup(const char *start, size_t len);

// ...........get_input.c
void	free_array(char **array);
char	**array_join(char **old_array, char *str_add);
char	**read_from_file(const char *s);


#endif