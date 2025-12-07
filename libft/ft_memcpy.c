/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaher <fdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:01:12 by fdaher            #+#    #+#             */
/*   Updated: 2024/06/14 17:06:28 by fdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*dest1;
	char	*src1;

	dest1 = (char *)dest;
	src1 = (char *)src;
	i = 0;
	while (i < n)
	{
		dest1[i] = src1[i];
		i++;
	}
	return (dest);
}

// #include <stdlib.h>
// #include <string.h>
// #include <stdio.h>
// int main()
// {
// 	const char s[] = "fatima ";
// 	char *d;
// 	d = (char *) malloc(sizeof(char)*(strlen(s)+1));
// 	ft_memcpy(d, s, 9);
// 	printf("%s",d);
// 	free(d);
// }