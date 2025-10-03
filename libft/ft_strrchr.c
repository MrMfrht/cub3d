/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaher <fdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:12:03 by fdaher            #+#    #+#             */
/*   Updated: 2024/06/19 13:41:56 by fdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = ft_strlen(s);
	while (s[i] != (unsigned char)c && i > 0)
		i--;
	if (s[i] == (unsigned char)c)
		return ((char *)&s[i]);
	return (0);
}

// #include <string.h>
// #include <stdio.h>
// int main()
// {
// 	char s[] = "tripouille";
//     // const char s[] = "12234";
//     printf("%s", ft_strrchr(s, 't' + 256));
// }