/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaher <fdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:40:19 by fdaher            #+#    #+#             */
/*   Updated: 2024/06/21 09:27:04 by fdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	lennb(long n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		i = 1;
		n = n * (-1);
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*s;
	long	num;

	num = (long)n;
	i = lennb(num);
	s = (char *)malloc(sizeof(char) * i + 1);
	if (!s)
		return (NULL);
	s[i] = '\0';
	if (num == 0)
		s[0] = '0';
	if (num < 0)
	{
		s[0] = '-';
		num = num * (-1);
	}
	while (num > 0)
	{
		s[i - 1] = (num % 10) + '0';
		num = num / 10;
		i--;
	}
	return (s);
}

// #include <stdio.h>
// int main()
// {
// 	printf("%s", ft_itoa(0));
// 	free(ft_itoa(0));
// }