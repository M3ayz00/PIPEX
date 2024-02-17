/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:37:21 by msaadidi          #+#    #+#             */
/*   Updated: 2024/02/17 15:48:46 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free2(char **path_list)
{
	int	i;

	i = 0;
	while (path_list[i])
	{
		free(path_list[i]);
		i++;
	}
	free(path_list);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

// custom error msg
int	ft_cerror(char *err)
{
	write(2, err, ft_strlen(err));
	return (1);
}

// error msg
void	ft_perror(char *err)
{
	perror(err);
	exit(1);
}

char	**get_path_list(char **env)
{
	int		i;
	char	**path_list;

	i = 0;
	while (env && env[i])
	{
		if (ft_memcmp(env[i], "PATH=", 5) == 0)
		{
			path_list = ft_split(env[i] + 5, ":");
			return (path_list);
		}
		i++;
	}
	return (NULL);
}
