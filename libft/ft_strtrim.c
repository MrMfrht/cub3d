/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaher <fdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:02:18 by fdaher            #+#    #+#             */
/*   Updated: 2025/10/03 14:15:22 by fdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*trim;

	while (!s1 || !set)
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
// 	const char	set[] = "	daherfaimaher    \n";
// 	const char	s1[] = "\t";


// 	// res = ft_strtrim(s1, set);
// 	// printf("->%s\n<-", res);
// 	printf("%s<_", ft_strtrim(s1,set));
// }