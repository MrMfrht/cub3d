/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaher <fdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:36:44 by fdaher            #+#    #+#             */
/*   Updated: 2024/06/14 17:05:31 by fdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 97 && c <= 122) || (c >= 65 && c <= 90) || (c >= 48 && c <= 57))
	{
		return (1);
	}
	return (0);
}

// int main()
// {
// 	printf("%d", ft_isalnum('4'));
// 	printf("%d", ft_isalnum('T'));
// 	printf("%d", ft_isalnum('d'));
// 	printf("%d", ft_isalnum('!'));
// 	return(0);
// }