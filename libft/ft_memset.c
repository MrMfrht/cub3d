/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaher <fdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:01:47 by fdaher            #+#    #+#             */
/*   Updated: 2024/06/17 13:20:35 by fdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned int	i;
	char			*s1;

	i = 0;
	s1 = (char *) s;
	while (i < n)
	{
		s1[i] = c;
		i++;
	}
	return (s);
}

// void	ft_putstr(char *str)
// {
// 	unsigned int	i;

// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		write (1, &str[i], 1);
// 		i++;
// 	}
// }

// int main()
// {
// 	char s[]= "fatima daher";
// 	ft_putstr(ft_memset(s, 'b', 7));
// }