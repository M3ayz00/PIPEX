/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m3ayz00 <m3ayz00@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 01:20:40 by m3ayz00           #+#    #+#             */
/*   Updated: 2024/02/12 02:53:40 by m3ayz00          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char    **get_cmd_path(char  **av, char **envp)
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
    return (cmd_path);
}

int open_infile(char *filename, int end[])
{
    int     fd;
    char    *infile;

    infile = ft_strtrim(filename, " ");
    fd = open(infile, O_RDONLY);
    free(infile);
    if (fd == -1)
    {
        close(end[0]);
        close(end[1]);
        perror("Error");
        exit(1);
    }
    return (fd);
}

int open_outfile(char *filename, int end[])
{
    int     fd;
    char    *outfile;

    outfile = ft_strtrim(filename, " ");
    fd = open(outfile, O_RDWR | O_CREAT | O_TRUNC, 0644);
    free(outfile);
    if (fd == -1)
    {
        close(end[0]);
        close(end[1]);
        perror("Error");
        exit(1);
    }
    return (fd);
}

char    **check_cmd_path(char **av, char **env, int end[], int fd)
{
    char    **cmd_path;

    cmd_path = get_cmd_path(av, env);
    if(!cmd_path)
    {
        close(fd);
        close(end[0]);
        close(end[1]);
        perror("Error");
        exit(1);
    }
    return (cmd_path);
}

void    setup_parent_redirection(int fd, int end[])
{
    close(end[1]); // close write-end
    dup2(fd, STDOUT_FILENO); // redirect output to outfile a.k.a outfile = stdout
    close(fd); // close outfile fd
    dup2(end[0], STDIN_FILENO); // redirect input to read-end a.k.a read-end = stdin
    close(end[0]); // close read-end
}

void    setup_child_redirection(int fd, int end[])
{
    close(end[0]);  // close read-end
    dup2(fd, STDIN_FILENO);// redirect input to infile a.k.a infile = stdin
    close(fd); // close infile fd
    dup2(end[1], STDOUT_FILENO); // redirect output to write-end a.k.a write-end = stdout
    close(end[1]); // close write-end fd
}

char    **get_cmd_args(char *command)
{
    char *cmd;
    char **cmd_args;

    cmd = ft_strtrim(command, " ");
    if (!cmd[0])
    {
        free(cmd);
        perror(command);
        exit(1);   
    }
    cmd_args = ft_split(cmd, ' '); 
    free(cmd);
    return (cmd_args);
}

void    child_process(char **av, char **env, int end[])
{
    int fd;
    char **cmd_path;
    char **cmd_args;

    
    fd = open_infile(av[1], end);
    cmd_path = check_cmd_path(av, env, end, fd);
    // write(2, "child_process function is called\n", 33);
    setup_child_redirection(fd, end);
    cmd_args = get_cmd_args(av[2]);
    if(execve(cmd_path[0], cmd_args, env) == -1)
    {
        ft_free2(cmd_args);
        ft_free2(cmd_path);
        ft_perror("execve");
    }
}

void    parent_process(char **av, char **env, int end[])
{
    int fd;
    char **cmd_path;
    char **cmd_args;

    fd = open_outfile(av[4], end);
    cmd_path = check_cmd_path(av, env, end, fd);
    setup_parent_redirection(fd, end);
    cmd_args = get_cmd_args(av[3]);
    if(execve(cmd_path[1], cmd_args, env) == -1)
    {
        ft_free2(cmd_args);
        ft_free2(cmd_path);
        ft_perror("execve");
    }
}