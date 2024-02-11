/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m3ayz00 <m3ayz00@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:37:21 by msaadidi          #+#    #+#             */
/*   Updated: 2024/02/10 22:15:34 by m3ayz00          ###   ########.fr       */
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
    str = ft_strtrim(str, " ");
    int i = 0;
    while(str[i] && str[i] != ' ')
        i++;
    char *first_word = malloc(sizeof(char) * i + 1);
    if (!first_word)
        return (NULL);
    i = 0;
    while(str[i] && str[i] != ' ')
    {
        first_word[i] = str[i];
        i++;
    }
    first_word[i] = '\0';
    free(str);
    return (first_word);
}

// void    check_cmds(char *c1, char *c2, char **envp)
// {
//     char    **cmd_path;
//     char    *cmd1;
//     char    *cmd2;

//     cmd1 = first_word(c1);
//     cmd2 = first_word(c2);
//     cmd_path = get_full_path(cmd1, cmd2, envp);
//     free(cmd1);
//     free(cmd2);
//     if (!cmd_path)
//         ft_perror("Invalid Command\n");
//     ft_free(cmd_path, 2);
// }

void    check_files(int ac, char **av)
{
    char    *infile;
    char    *outfile;
    
    if (ac != 5 || !av[2][0] || !av[3][0] || !av[4][0])
        ft_perror("Error: Invalid arguments.\n");
    infile = ft_strtrim(av[1], " ");
    outfile = ft_strtrim(av[4], " ");
    if (access(infile, F_OK & R_OK) == -1)
    {
        perror("Infile error");
        free(infile);
        free(outfile);
        exit(1);    
    }
    if (access(outfile, F_OK) == 0)
    {
        if (access(outfile, W_OK) == -1)
        {
            perror("Outfile error");
            free(infile);
            free(outfile);
            exit(1);
        }
    }
    free(infile);
    free(outfile);
}

char    *join_path(char **path_list, int i, char *cmd)
{
    int path_len;
    int full_len;
    char    *full_path;
    
    path_len = ft_strlen(path_list[i]);
    full_len = path_len + ft_strlen(cmd) + 2; // 2 for '/' and '\0'
    full_path = (char *)malloc(full_len);
    if (!full_path)
        return (NULL);
    ft_memcpy(full_path, path_list[i], path_len);// Construct the full path
    full_path[path_len] = '/';
    ft_memcpy(full_path + path_len + 1, cmd, ft_strlen(cmd));
    full_path[full_len - 1] = '\0';
    return (full_path);
}

char    **check_x_ok(char **path_list, char *cmd1, char *cmd2, int *j)
{
    char    **full_path;

    while (path_list[*j])// Iterate through each path in PATH
    {
        full_path = malloc(2 * sizeof(char *));
        full_path[0] = join_path(path_list, *j, cmd1);
        full_path[1] = join_path(path_list, *j, cmd2);
        if (!full_path[0] || !full_path[1])
            return (NULL);
        if (access(full_path[0], X_OK) == 0 && access(full_path[1], X_OK) == 0)// Check if the full path is executable
        {
            path_list = ft_free(path_list, *j + 1);
            return (full_path);
        }
        ft_free(full_path, 2);
        (*j)++;
    }
    return (NULL);
}

char    **get_full_path(char *cmd1, char *cmd2, char **env) {
    int i = 0;
    char *path_env = NULL;
    char **full_path = NULL;

    if(!cmd1 || !cmd2 || !env)
        return (NULL);
    while (env[i] && ft_memcmp(env[i], "PATH=", 5) != 0)// Find the PATH environment variable
        i++;
    if (env[i] && ft_memcmp(env[i], "PATH=", 5) == 0) 
    {
        path_env = env[i] + 5; // Skip "PATH="
        char **path_list = ft_split(path_env, ':'); 
        if (!path_list)
            return (NULL);
        i = 0;
        full_path = check_x_ok(path_list, cmd1, cmd2, &i);
        if (!full_path)
        {
            path_list = ft_free(path_list, i);
            return (NULL);
        }
        else
            return (full_path);
    }
    return (NULL);
}

