/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:37:21 by msaadidi          #+#    #+#             */
/*   Updated: 2024/02/13 17:23:38 by msaadidi         ###   ########.fr       */
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

//custom error msg
void    ft_cerror(char *err)
{
    write(2, err, ft_strlen(err));
    exit(1);
}

//error msg
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





