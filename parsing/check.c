/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaher <fdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 14:17:00 by fdaher            #+#    #+#             */
/*   Updated: 2025/10/03 15:17:14 by fdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_cub(char *str)
{
	char	*extension;

	extension = ft_strrchr(str, '.');
	if (!extension)
		return (0);
	if (ft_strncmp(extension, ".cub", 4) == 0)
		return (1);
	return (0);
}

int	check_xpm(char *str)
{
	char	*extension;

	extension = ft_strrchr(str, '.');
	if (!extension)
		return (0);
	if (ft_strncmp(extension, ".xpm", 4) == 0)
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
