/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salegari <salegari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/22 21:33:02 by salegari          #+#    #+#             */
/*   Updated: 2026/08/22 21:33:12 by salegari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_checkset(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_wordc(char *str, char *set)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (str[i])
	{
		while (str[i] && ft_checkset(str[i], set))
			i++;
		if (str[i])
			words++;
		while (str[i] && !ft_checkset(str[i], set))
			i++;
	}
	return (words);
}

int	ft_wordlen(char *str, char *set)
{
	int	i;

	i = 0;
	while (str[i] && !ft_checkset(str[i], set))
		i++;
	return (i);
}

char	*ft_strncpy(char *src, int n)
{
	char	*dest;
	int		i;

	dest = malloc((n + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	**ft_split(char *str, char *charset)
{
	char	**arr;
	int		i;
	int		len;

	arr = malloc((ft_wordc(str, charset) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	len = 0;
	while (*str)
	{
		while (*str && ft_checkset(*str, charset))
			str++;
		if (*str)
		{
			len = ft_wordlen(str, charset);
			arr[i++] = ft_strncpy(str, len);
			str += len;
		}
	}
	arr[i] = NULL;
	return (arr);
}
