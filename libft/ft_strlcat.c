/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaher <fdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:08:52 by fdaher            #+#    #+#             */
/*   Updated: 2024/06/15 10:08:14 by fdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	lendst;
	size_t	lensrc;
	size_t	i;

	lendst = ft_strlen(dst);
	lensrc = ft_strlen(src);
	i = 0;
	if (size <= lendst)
		return (size + lensrc);
	while (src[i] != '\0' && (lendst + i) < size -1)
	{
		dst[lendst + i] = src[i];
		i++;
	}
	dst[lendst + i] = '\0';
	return (lendst + lensrc);
}

// #include <bsd/string.h>
// #include <stdio.h>
// #include <string.h>
// int main()
// {
//     char d[20] = "";
//     const char s[20] = "123";
//     size_t len = ft_strlcat(d, s, 7);
//     printf("%ld\n%s", len, d);
// }