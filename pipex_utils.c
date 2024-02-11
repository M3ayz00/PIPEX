/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m3ayz00 <m3ayz00@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 01:20:40 by m3ayz00           #+#    #+#             */
/*   Updated: 2024/02/10 22:28:59 by m3ayz00          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char    *get_cmd_path(char  **av, char **envp, int i)
{
    char    **cmd_path;
    char    *cmd1;
    char    *cmd2;
    
    cmd1 = first_word(av[2]);
    cmd2 = first_word(av[3]);
    cmd_path = get_full_path(cmd1, cmd2, envp);
    free(cmd1);
    free(cmd2);
    if (!cmd_path)
        return (NULL);
    return (cmd_path[i]);
}

void    child_process(char **av, char **env, int end[])
{
    char *infile;
    char *cmd;
    char *cmd_path;
    char **cmd_args;
    int fd;

    infile = ft_strtrim(av[1], " ");
    fd = open(infile, O_RDONLY);
    free(infile);
    if (fd == -1)
    {
        close(end[0]);
        close(end[1]);
        perror("Error");
        exit(1);
    }
    cmd_path = get_cmd_path(av, env, 0);
    if(!cmd_path)
    {
        close(fd);
        close(end[0]);
        close(end[1]);
        perror(av[2]);
        exit(1);
    }
    // child process
    close(end[0]);  // close read-end
    dup2(fd, STDIN_FILENO);// redirect input to infile a.k.a infile = stdin
    close(fd); // close infile fd
    dup2(end[1], STDOUT_FILENO); // redirect output to write-end a.k.a write-end = stdout
    close(end[1]); // close write-end fd
    cmd = ft_strtrim(av[2], " ");
    cmd_args = ft_split(cmd, ' '); // split command and options
    if(execve(cmd_path, cmd_args, env) == -1) // execute cmd with options
        perror("execve");
}

void    parent_process(char **av, char **env, int end[])
{
    char *outfile;
    char *cmd;
    char *cmd_path;
    char **cmd_args;
    int fd;

    outfile = ft_strtrim(av[4], " ");
    fd = open(outfile, O_RDWR | O_CREAT | O_TRUNC, 0644);
    free(outfile);
    if (fd == -1)
    {
        close(end[0]);
        close(end[1]);
        perror("Error");
        exit(1);
    }
    cmd_path = get_cmd_path(av, env, 1);
    if(!cmd_path)
    {
        close(fd);
        close(end[0]);
        close(end[1]);
        perror(av[3]);
        exit(1);
    }
    close(end[1]); // close write-end 
    dup2(fd, STDOUT_FILENO); // redirect output to outfile a.k.a outfile = stdout
    close(fd); // close outfile fd
    dup2(end[0], STDIN_FILENO); // redirect input to read-end a.k.a read-end = stdin
    close(end[0]); // close read-end
    cmd = ft_strtrim(av[3], " ");
    cmd_args = ft_split(cmd, ' '); 
    if(execve(cmd_path, cmd_args, env) == -1)
        perror("execve");
}