/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaher <fdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:24:11 by fdaher            #+#    #+#             */
/*   Updated: 2024/06/19 13:00:27 by fdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*d1;
	unsigned char	*d2;

	i = 0;
	d1 = (unsigned char *)s1;
	d2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (d1[i] == d2[i] && i < n -1)
		i++;
	return (d1[i] - d2[i]);
}

// #include <string.h>
// #include <stdio.h>
// int main()
// {
// 	char s[] = {-128, 0, 127, 0};
// 	char s2[] = {0, 0, 127, 0};
//     // const char s1[] = "10445";
// 	// const char s2[] = "14245";
// 	printf ("%d", ft_memcmp(s, s2, 1));
// }