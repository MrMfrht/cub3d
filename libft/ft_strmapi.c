/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaher <fdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:42:10 by fdaher            #+#    #+#             */
/*   Updated: 2024/06/18 10:51:53 by fdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*res;
	unsigned int	i;

	i = 0;
	if (!s || !f)
		return (NULL);
	res = (char *)malloc(sizeof(char) * (ft_strlen(s) +1));
	if (!res)
		return (NULL);
	while (s[i])
	{
		res[i] = f(i, s[i]);
		i++;
	}
	res[i] = '\0';
	return (res);
}

// char f(unsigned int index, char c)
// {
// 	if (c >= 'a' && c <= 'z')
// 		return c - 32; // Convert to uppercase
// 	else
// 		return (index + '0'); // Return unchanged for non-lowercase characters
// }
// #include <stdio.h>
// int main()
// {
// 	const char s[]= "fAtimaD";
// 	char *res;
// 	res = ft_strmapi(s, f);
// 	printf("%s", res);
// }