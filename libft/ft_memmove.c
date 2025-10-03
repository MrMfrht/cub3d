/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaher <fdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:04:41 by fdaher            #+#    #+#             */
/*   Updated: 2024/06/15 12:21:13 by fdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*dest1;
	char	*src1;

	dest1 = (char *)dest;
	src1 = (char *)src;
	i = 0;
	if (dest1 > src1)
	{
		while (n-- > 0)
		{
			dest1[n] = src1[n];
		}
	}
	else
	{
		while (i < n)
		{
			dest1[i] = src1[i];
			i++;
		}
	}
	return (dest);
}

// #include <stdio.h>
// #include <string.h>
// int main()
// {
//     char str1[] = "6789";
//     char str2[] = "12345";

//     printf("str1: %s\n", str1);
//     printf("str2: %s\n", str2);

//     ft_memmove(str1, str2, 6);
//     printf("\n");
//     printf("str1: %s\n", str1);
//     printf("str2: %s\n", str2);
//     return 0;
// }

// int main ()
// {
// 	char dest[] = "6789";
// 	char	*s = "12345";
// 	memmove(dest, s, 5);
// 	printf("%s", dest);
// }
// if (n > ft_strlen((const char *) dest))
	// 	while (i < n)
	// 	{
	// 		dest1[i] = src1[i];
	// 		i++;
	// 	}
