/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaher <fdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:02:18 by fdaher            #+#    #+#             */
/*   Updated: 2025/10/08 11:51:45 by fdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*trim;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[start]) && start < ft_strlen(s1))
		start++;
	while (ft_strchr(set, s1[end]) && start < end)
		end--;
	if (start > end)
		return (ft_substr("", 0, 0));
	trim = ft_substr(s1, start, end - start + 1);
	if (!trim)
		return (NULL);
	return (trim);
}

// # include <stdio.h>
// int	main(void)
// {
// 	char	*set;
// 	char	*s1;
// 	s1  = "middle space   here    ";
// 	set = " ";
// 	printf("->%s<-", ft_strtrim(s1," "));
// }