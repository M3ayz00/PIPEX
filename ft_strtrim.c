/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m3ayz00 <m3ayz00@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:38:49 by msaadidi          #+#    #+#             */
/*   Updated: 2024/02/10 20:51:54 by m3ayz00          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_strchr(char *str, int c)
{
	while (str && *str)
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	if (*str == '\0' && (char)c == '\0')
		return ((char *)str);
	return (NULL);
}

static int	ft_start(char *set, char *s)
{
	int	i;

	i = 0;
	while (s[i] && (ft_strchr(set, s[i])))
		i++;
	return (i);
}

static int	ft_end(char *set, char *s)
{
	int	j;

	j = ft_strlen(s) - 1;
	while (j > 0 && (ft_strchr(set, s[j])))
		j--;
	return (j);
}

char	*ft_strtrim(char *s, char *set)
{
	unsigned int	i;
	unsigned int	j;
	char			*tmp;

	if (!s || !set)
		return (NULL);
	i = ft_start(set, s);
	j = ft_end(set, s);
	j++;
	if (i < j)
	{
		tmp = ft_calloc(j - i + 1, sizeof(char));
		if (!tmp)
			return (NULL);
		ft_memcpy(tmp, s + i, j - i);
	}
	else
	{
		tmp = ft_calloc(1, sizeof(char));
		if (!tmp)
			return (NULL);
	}
	return (tmp);
}