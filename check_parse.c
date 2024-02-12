/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:37:21 by msaadidi          #+#    #+#             */
/*   Updated: 2024/02/12 16:25:36 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void ft_free2(char **path_list) 
{
    int i;
    
    i = 0;
    while (path_list[i]) 
    {
        free(path_list[i]);
        i++;
    }
    free(path_list);
}


int ft_strlen(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return (i);
}

void    ft_perror(char *err)
{
    perror(err);
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

void    perror_strs(char *infile, char *outfile, char *str)
{
    perror(str);
    free(infile);
    free(outfile);
    exit(1);
}


void    check_commands(int ac, char **av)
{
    char    *cmd1;
    char    *cmd2;
    
    if (ac != 5 || !av[2][0] || !av[3][0])
        ft_perror("Error");
    cmd1 = ft_strtrim(av[2], " ");
    cmd2 = ft_strtrim(av[3], " ");
    if (!cmd1[0] || !cmd2[0])
        perror_strs(cmd1, cmd2, "command not found");
    free(cmd1);
    free(cmd2);
}

void    check_files(int ac, char **av)
{
    char    *infile;
    char    *outfile;
    
    if (ac != 5 || !av[1][0] || !av[4][0])
        ft_perror("Error\n");
    infile = ft_strtrim(av[1], " ");
    outfile = ft_strtrim(av[4], " ");
    if (!infile[0] || !outfile[0])
        perror_strs(infile, outfile, "Error");
    if (access(infile, F_OK & R_OK) == -1)
        perror_strs(infile, outfile, "Infile");
    if (access(outfile, F_OK) == 0)
        if (access(outfile, W_OK) == -1)
            perror_strs(infile, outfile, "Outfile");
    free(infile);
    free(outfile);
}

void    check_args(int ac, char **av)
{
    check_files(ac, av);
    check_commands(ac, av);
}

char    *join_path(char *path, char *cmd)
{
    int     path_len;
    int     full_len;
    char    *full_path;
    
    if (!path)
        return (NULL);
    path_len = ft_strlen(path);
    full_len = path_len + ft_strlen(cmd) + 2; // 2 for '/' and '\0'
    full_path = (char *)malloc(full_len);
    if (!full_path)
        return (NULL);
    ft_memcpy(full_path, path, path_len);// Construct the full path
    full_path[path_len] = '/';
    ft_memcpy(full_path + path_len + 1, cmd, ft_strlen(cmd));
    full_path[full_len - 1] = '\0';
    return (full_path);
}

char    **find_executable_path(char **path_list, char *cmd1, char *cmd2)
{
    char    **full_path;
    int found1;
    int found2;
    int     i;

    i = 0;
    found1 = 0;
    found2 = 0;
    full_path = ft_calloc(2, sizeof(char *));
    if (!full_path)
    {
        ft_free2(path_list);
        return (NULL);
    }
    while (path_list[i] && !(found1 && found2))// Iterate through each path in PATH
    {
        // printf("%s\n", path_list[i]);
        if(!found1)
        {
            full_path[0] = join_path(path_list[i], cmd1);
            if (!full_path[0])
                return (NULL);
            // printf("==>%s\n", full_path[0]);
            if (access(full_path[0], X_OK) == 0)// Check if the full path is executable   
                found1 = 1;
            else
                free(full_path[0]);
        }
        if(!found2)
        {
            full_path[1] = join_path(path_list[i], cmd2);
            if (!full_path[1])
                return (NULL);
            // printf("==>%s\n", full_path[1]);
            if (access(full_path[1], X_OK) == 0)// Check if the full path is executable   
                found2 = 1;
            else
                free(full_path[1]);
        }
        i++;
    }
    if (found1 && found2)
        return (full_path);
    free(full_path);
    return (NULL);
}

char    **get_path_list(char **env)
{
    int i;
    char    **path_list;

    i = 0;
    while (env[i])
    {
        if (ft_memcmp(env[i], "PATH=", 5) == 0)
        {
            path_list = ft_split(env[i] + 5, ':');
            return (path_list);
        }
        i++;
    }
    return (NULL);
}



char    **get_full_path(char *cmd1, char *cmd2, char **env) 
{
    char **path_list;
    char **full_path;

    if(!cmd1 || !cmd2 || !env)
        return (NULL);
    path_list = get_path_list(env);
    if (!path_list)
        return (NULL);
    full_path = ft_calloc(2, sizeof(char *));
    if (!full_path)
    {
        ft_free2(path_list);
        return (NULL);
    }
    full_path = find_executable_path(path_list, cmd1, cmd2);
    ft_free2(path_list);
    if (full_path == NULL)
        return (NULL);
    return (full_path);
}

