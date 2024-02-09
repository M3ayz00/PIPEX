/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m3ayz00 <m3ayz00@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:37:21 by msaadidi          #+#    #+#             */
/*   Updated: 2024/02/08 21:32:42 by m3ayz00          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int ft_strlen(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return (i);
}

void    ft_perror(char *err)
{
    write(2, err, ft_strlen(err));
    exit(1);
}
char    *first_word(char *str)
{
    int i = 0;
    while(str[i] && str[i] != ' ')
        i++;
    char *first_word = malloc(sizeof(char) * i + 1);
    if (!first_word)
        ft_perror("Allocation failed.\n");
    i = 0;
    while(str[i] && str[i] != ' ')
    {
        first_word[i] = str[i];
        i++;
    }
    first_word[i] = '\0';
    return (first_word);
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
    if (ac != 5 || !av[2][0] || !av[3][0] || !av[4][0])
        ft_perror("Error: Invalid arguments.\n");
    if (access(av[1], R_OK) == -1)
        ft_perror("Error: Permission denied.\n");
    if (access(av[4], F_OK) == 0)
    {
        if (access(av[4], R_OK | W_OK) == -1)
            ft_perror("Error: Permission denied.\n");
    }
}

int    is_file_valid(char *path)
{
    int fd;

    fd = open(path, O_RDWR);
    if (fd == -1)   
        perror("Error");
    return (fd);
}

void is_cmd_valid(char *cmd, char **env) {
    int i = 0;
    char *path_env = NULL;

    while (env[i] && ft_memcmp(env[i], "PATH=", 5) != 0)// Find the PATH environment variable
        i++;
    if (env[i] && ft_memcmp(env[i], "PATH=", 5) == 0) 
    {
        path_env = env[i] + 5; // Skip "PATH="
        char **path_list = ft_split(path_env, ':'); 
        if (!path_list)
            ft_perror("Error: Failed split.\n");
        int j = 0;
        while (path_list[j])// Iterate through each path in PATH
        {
            int path_len = ft_strlen(path_list[j]);
            int full_len = path_len + ft_strlen(cmd) + 2; // 2 for '/' and '\0'
            char *full_path = (char *)malloc(full_len);
            if (!full_path)
            {
                ft_free(path_list, j + 1);
                ft_perror("Error: Allocation failed.\n");
            }
            ft_memcpy(full_path, path_list[j], path_len);// Construct the full path
            full_path[path_len] = '/';
            ft_memcpy(full_path + path_len + 1, cmd, ft_strlen(cmd));
            full_path[full_len - 1] = '\0';
            if (access(full_path, X_OK) == 0)// Check if the full path is executable
            {
                free(full_path);
                ft_free(path_list, j + 1);
                return;
            }
            free(full_path);
            j++;
        }
        ft_free(path_list, j);
    }
    ft_perror("Error: Invalid command.\n");
}
