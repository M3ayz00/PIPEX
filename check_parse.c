/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:37:21 by msaadidi          #+#    #+#             */
/*   Updated: 2024/02/09 16:54:52 by msaadidi         ###   ########.fr       */
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

void    check_args(int ac, char **av)
{
    if (ac != 5 || !av[2][0] || !av[3][0] || !av[4][0])
        ft_perror("Error: Invalid arguments.\n");
    if (access(av[1], R_OK) == -1)
        ft_perror("Error: Permission denied.\n");
    if (access(av[4], F_OK) == 0)
    {
        if (access(av[4], W_OK) == -1)
        {
            perror("Outfile error");
            exit(1);
        }
    }
}

char    *get_full_path(char **path_list, int i, char *cmd)
{
    int path_len;
    int full_len;
    char    *full_path;
    
    path_len = ft_strlen(path_list[i]);
    full_len = path_len + ft_strlen(cmd) + 2; // 2 for '/' and '\0'
    full_path = (char *)malloc(full_len);
    if (!full_path)
    {
        ft_free(path_list, i + 1);
        ft_perror("Error: Memory allocation failed.\n");
        return (NULL);
    }
    ft_memcpy(full_path, path_list[i], path_len);// Construct the full path
    full_path[path_len] = '/';
    ft_memcpy(full_path + path_len + 1, cmd, ft_strlen(cmd));
    full_path[full_len - 1] = '\0';
    return (full_path);
}

char    *check_x_ok(char **path_list, char *cmd)
{
    int j = 0;
    char    *full_path;
    while (path_list[j])// Iterate through each path in PATH
    {
        full_path = get_full_path(path_list, j, cmd);
        if (access(full_path, X_OK) == 0)// Check if the full path is executable
        {
            printf("%s\n", full_path);
            ft_free(path_list, j + 1);
            return (full_path);
        }
        free(full_path);
        j++;
    }
    ft_free(path_list, j);
    return (NULL);
}

char    *is_cmd_valid(char *cmd, char **env) {
    int i = 0;
    char *path_env = NULL;
    char *full_path = NULL;

    if(!cmd || !env)
    {
        ft_perror("Error: Invalid input.\n");
        return (NULL);
    }
    while (env[i] && ft_memcmp(env[i], "PATH=", 5) != 0)// Find the PATH environment variable
        i++;
    if (env[i] && ft_memcmp(env[i], "PATH=", 5) == 0) 
    {
        path_env = env[i] + 5; // Skip "PATH="
        char **path_list = ft_split(path_env, ':'); 
        if (!path_list) 
            return (NULL);
        full_path = check_x_ok(path_list, cmd);
        if (!full_path)
            return (NULL);
        else
            return (full_path);
    }
    return (NULL);
}

