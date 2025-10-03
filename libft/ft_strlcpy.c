/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaher <fdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:43:12 by fdaher            #+#    #+#             */
/*   Updated: 2024/06/20 10:45:10 by fdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (src[i] && i < (size - 1))
	{
		dst[i] = src[i];
		i++;
	}
	if (i < size)
		dst[i] = '\0';
	return (ft_strlen(src));
}

// #include <bsd/string.h>
// #include <string.h>
// #include <stdio.h>
// int main()
// {
// 	char d[10];
// 	const char s[] = "fatimadah";
// 	size_t	len;
// 	len = ft_strlcpy(d, s, 5);
// 	printf("%ld \n %s", len, d);
// }