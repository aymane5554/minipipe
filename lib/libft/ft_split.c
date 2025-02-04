/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 23:25:55 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/01/26 12:41:28 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*ft_strindup(char *src, char c)
{
	int		i;
	char	*s;

	i = 0;
	if (c == '\'')
		src++;
	while (src[i] != '\0' && src[i] != c)
		i++;
	s = (char *)malloc(i + 1);
	if (!s)
		return (free(s), NULL);
	i = 0;
	while (src[i] != '\0' && src[i] != c)
	{
		s[i] = src[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

static	int	word_count(char	*s, char c)
{
	int		arr[3];
	char	tmp;

	if (s == NULL)
		return (-100);
	ft_bzero(arr, 12);
	tmp = c;
	while (s[arr[0]])
	{
		if (s[arr[0]] == c)
		{
			arr[1] = 0;
			c = tmp;
		}
		else if (s[arr[0]] != c && arr[1] == 0)
		{
			if (s[arr[0]] == '\'')
				c = s[arr[0]];
			arr[1] = 1;
			arr[2]++;
		}
		arr[0]++;
	}
	return (arr[2]);
}

static void	*free_all(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr[i]);
	free(arr);
	return (NULL);
}

static void	setvars(int arr[3], char *tmp, char *c, char idk)
{
	if (idk == 0)
	{
		ft_bzero(arr, 12);
		*tmp = *c;
	}
	else if (idk == 1)
	{
		arr[2] = 0;
		*c = *tmp;
	}
}

char	**ft_split(char const *s, char c)
{
	int		iterators[3];
	char	**arr;
	char	tmp;

	setvars(iterators, &tmp, &c, 0);
	arr = (char **)malloc((word_count((char *)s, c) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	while (s[iterators[0]])
	{
		if (s[iterators[0]] == c)
			setvars(iterators, &tmp, &c, 1);
		else if (s[iterators[0]] != c && iterators[2] == 0)
		{
			if (s[iterators[0]] == '\'')
				c = s[iterators[0]];
			arr[iterators[1]] = ft_strindup((char *)(s + iterators[0]), c);
			if (arr[iterators[1]] == NULL)
				return (free_all(arr));
			iterators[2] = 1;
			iterators[1]++;
		}
		iterators[0]++;
	}
	return (arr[iterators[1]] = NULL, arr);
}
