/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:27:30 by msaadidi          #+#    #+#             */
/*   Updated: 2024/02/17 15:47:21 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_wordlen(char const *s, char *set)
{
	int	i;

	i = 0;
	while (s[i] && !is_c_in_set(s[i], set))
		i++;
	return (i);
}

int	ft_wordcount(char const *s, char *set)
{
	int	i;
	int	w;

	w = 0;
	while (*s)
	{
		while (*s && is_c_in_set(*s, set))
			s++;
		i = ft_wordlen(s, set);
		s += i;
		if (i)
			w++;
	}
	return (w);
}

static char	*ft_wordcpy(char const *src, int n)
{
	char	*dest;

	dest = malloc((n + 1) * sizeof(char));
	if (!dest)
		return (0);
	dest[n] = '\0';
	while (n--)
		dest[n] = src[n];
	return (dest);
}

static char	**ft_free(char **str, size_t n)
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
	return (NULL);
}

char	**ft_split(char const *s, char *set)
{
	char	**t;
	int		size;
	int		i;
	int		n;

	if (!s)
		return (0);
	size = ft_wordcount(s, set);
	t = malloc((size + 1) * sizeof(char *));
	if (!t)
		return (NULL);
	i = -1;
	while (++i < size)
	{
		while (*s && is_c_in_set(*s, set))
			s++;
		n = ft_wordlen(s, set);
		if (*s)
			t[i] = ft_wordcpy(s, n);
		if (!t[i])
			return (ft_free(t, i));
		s += n;
	}
	t[size] = 0;
	return (t);
}
