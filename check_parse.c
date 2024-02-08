/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m3ayz00 <m3ayz00@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:37:21 by msaadidi          #+#    #+#             */
/*   Updated: 2024/02/08 02:30:53 by m3ayz00          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    ft_perror(void)
{
    perror("Error");
    exit(1);
}


int ft_strlen(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return (i);
}
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	unsigned char		*s;

	if (!src && !dest)
		return (NULL);
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	while (n--)
		*d++ = *s++;
	return (dest);
}

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	const unsigned char	*s1;
	const unsigned char	*s2;
	size_t				i;

	s1 = (const unsigned char *)str1;
	s2 = (const unsigned char *)str2;
	i = 0;
	while (s1 && s2 && i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

void    check_args(int ac, char **av)
{
    if (ac != 5)
    {
        printf("Error: Arguments non valid.\n");
        exit(1);
    }
    if (access(av[1], R_OK) == -1)
        ft_perror();
    if (!av[2][0] || !av[3][0] || !av[4][0])
        ft_perror();
}

int    is_file_valid(char *path)
{
    int fd;

    fd = open(path, O_RDWR);
    if (fd == -1)
        ft_perror();
    return (fd);
}

void    is_cmd_valid(char *cmd, char **env)
{
    int i;
    int j;
    char    **path_list;
    char    *path;
    int cmd_len = ft_strlen(cmd);
    char **tmp = env;

    i = 0;
    while(tmp[i]&& ft_memcmp(tmp[i], "PATH=", 5) != 0)
        i++;
    if(ft_memcmp(tmp[i], "PATH=", 5) == 0)
    {
        tmp += i;
        *tmp += 5;
        path_list = ft_split(*tmp, ':');
        if (!path_list)
            ft_perror();
        j = 0;
        while (path_list[j])
        {
            int path_len = ft_strlen(path_list[j]);
            int full_len = path_len + cmd_len;
            path = (char *)malloc(sizeof(char) * full_len + 2);
            if (!path)
                ft_perror();
            ft_memcpy(path, path_list[j], path_len);
            ft_memcpy(path + path_len, "/", 1);
            ft_memcpy(path + path_len + 1, cmd, cmd_len);
            path[full_len + 1] = '\0';
            j++;
            if (access(path, X_OK) == 0)
            {
                printf("%s\n", path);
                free(path);
                path_list = ft_free(path_list, j);
                return;
            }
            free(path);
        }
        path_list = ft_free(path_list, j);
        ft_perror();
    }
}