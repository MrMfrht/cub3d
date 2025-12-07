/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaher <fdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:09:32 by fdaher            #+#    #+#             */
/*   Updated: 2024/06/15 16:59:39 by fdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

void	ft_bzero(void *s, size_t n)
{
	unsigned int	i;
	char			*s1;

	i = 0;
	s1 = (char *)s;
	while (i < n)
	{
		s1[i] = '\0';
		i++;
	}
}

// #include <stdio.h>
// int main()
// {
// 	char s[] = "fatima daher";
// 	ft_bzero(s, 3);
// 	printf("%s", s);
// }