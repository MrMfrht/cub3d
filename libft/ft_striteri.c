/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaher <fdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:44:25 by fdaher            #+#    #+#             */
/*   Updated: 2024/06/18 13:41:46 by fdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

// #include <stdio.h>
// void	f(unsigned int i, char *s)
// {
// 	printf("the pointer %s with the index %d", s, i);
// }

// int main()
// {
// 	char s[] ="ahd";
// 	printf("%s\n", s);
// 	ft_striteri(s, f);
// }