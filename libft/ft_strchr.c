/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaher <fdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:08:19 by fdaher            #+#    #+#             */
/*   Updated: 2024/06/19 13:35:44 by fdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i] && s[i] != (unsigned char) c)
		i++;
	if (s[i] == (unsigned char)c)
		return ((char *)&s[i]);
	return (0);
}

// #include <string.h>
// #include <stdio.h>
// int main()
// {
// 	// char s[] = "tripouille";
// 	const char s[] = "er.tdjh.1j45";
//     printf("%s", ft_strchr(s, '.'));
// }
