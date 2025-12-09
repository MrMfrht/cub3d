/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaher <fdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 14:17:00 by fdaher            #+#    #+#             */
/*   Updated: 2025/12/09 13:26:43 by fdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_cub(char *str)
{
	char	*extension;

	extension = ft_strrchr(str, '.');
	if (!extension)
		return (0);
	if (ft_strncmp(extension, ".cub", 4) == 0 && ft_strlen(extension) == 4)
		return (1);
	return (0);
}

int	check_xpm(char *str)
{
	char	*extension;

	extension = ft_strrchr(str, '.');
	if (!extension)
		return (0);
	if (ft_strncmp(extension, ".xpm", 4) == 0 && ft_strlen(extension) == 4)
		return (1);
	return (0);
}

char	*ft_strndup(const char *start, size_t len)
{
	char	*dup;
	char	*des;
	size_t	i;

	i = 0;
	dup = (char *) malloc (sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	des = (char *)start;
	while (des[i] && i < len)
	{
		dup[i] = des[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

// malloc for texture_node
t_texture	*create_texture(void)
{
	t_texture	*node;

	node = (t_texture *)malloc(sizeof(t_texture));
	if (!node)
		return (NULL);
	node->no = NULL;
	node->so = NULL;
	node->we = NULL;
	node->ea = NULL;
	node->f = NULL;
	node->c = NULL;
	return (node);
}

// free for texture_node and char *
void	free_texture(t_texture *node)
{
	if (!node)
		return ;
	if (node->no)
		free(node->no);
	if (node->so)
		free(node->so);
	if (node->we)
		free(node->we);
	if (node->ea)
		free(node->ea);
	if (node->f)
		free(node->f);
	if (node->c)
		free(node->c);
	if (node)
		free(node);
}

// int main(void)
// {
// 	t_texture	*node;

// 	node = create_texture();
// 	node->no = ft_strdup("t_no");
// 	node->so = ft_strdup("t_so");
// 	node->we = ft_strdup("t_we");
// 	node->ea = ft_strdup("t_ea");
// 	node->f = ft_strdup("t_f");
// 	node->c = ft_strdup("t_c");
// 	if (node)
// 	{
// 		printf("%s %s %s %s %s %s ",
// 			node->no, node->so, node->we, node->ea, node->c, node->f);
// 	}
// 	free_texture(node);
// }
