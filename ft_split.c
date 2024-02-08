/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m3ayz00 <m3ayz00@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:27:30 by msaadidi          #+#    #+#             */
/*   Updated: 2024/02/08 02:02:36 by m3ayz00          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_wordlen(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static int	ft_wordcount(char const *s, char c)
{
	int	i;
	int	w;

	w = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		i = ft_wordlen(s, c);
		s += i;
		if (i)
			w++;
	}
	return (w);
}

static char	*ft_wordcpy(char const *src, int n)
{
	char	*dest;

	dest = malloc((n + 2) * sizeof(char));
	if (!dest)
		return (0);
	dest[n] = '\0';
	dest[n - 1] = '/';
	while (n--)
		dest[n] = src[n];
	return (dest);
}

char	**ft_free(char **str, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**t;
	int		size;
	int		i;
	int		n;

	if (!s)
		return (0);
	size = ft_wordcount(s, c);
	t = malloc((size + 1) * sizeof(char *));
	if (!t)
		return (0);
	i = -1;
	while (++i < size)
	{
		while (*s && *s == c)
			s++;
		n = ft_wordlen(s, c);
		if (*s)
			t[i] = ft_wordcpy(s, n);
		if (!t[i])
			return (ft_free(t, i));
		s += n;
	}
	t[size] = 0;
	return (t);
}
