/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaher <fdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:35:30 by fdaher            #+#    #+#             */
/*   Updated: 2024/06/20 18:12:46 by fdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stddef.h>

static size_t	word(const char *s, char c)
{
	size_t	word;
	size_t	m_word;
	size_t	i;

	word = 0;
	m_word = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && m_word == 0)
		{
			m_word = 1;
			word++;
		}
		if (s[i] == c)
			m_word = 0;
		i++;
	}
	return (word);
}

static void	free_arr(char **arr, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (arr[i])
			free (arr[i]);
		i++;
	}
	free (arr);
}

static size_t	len_word(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	**split(const char *s, char c, char **arr, size_t word)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < word)
	{
		while (s[j] && s[j] == c)
			j++;
		arr[i] = ft_substr(s, j, len_word(&s[j], c));
		if (!arr[i])
		{
			free_arr(arr, i);
			return (NULL);
		}
		while (s[j] && s[j] != c)
			j++;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	nbword;

	if (!s)
		return (NULL);
	nbword = word(s, c);
	arr = (char **)malloc(sizeof(char *) * (nbword + 1));
	if (!arr)
		return (NULL);
	arr = split(s, c, arr, nbword);
	return (arr);
}

// #include <stdio.h>
// int main()
// {
// 	char s[30] = "cfatcimacdahercccgs";
// 	char **arr = ft_split(s, 'c');
// 	// size_t i = 0;
// 	printf("%ld\n", word(s, 'c'));
// 	printf("%s", arr[]);
// }
