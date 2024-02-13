/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 01:20:40 by m3ayz00           #+#    #+#             */
/*   Updated: 2024/02/13 17:25:06 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_full_path(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, F_OK) == 0)  
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

static char    *get_cmd_path(char **paths, char  *command)
{
    char    *cmd_path;
    char    *cmd;
    
    cmd = first_word(command);
    cmd_path = get_full_path(paths, cmd);
    free(cmd);
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
void    close_pipes(t_pipex *pipex)
{
    close(pipex->end[0]);
    close(pipex->end[1]);
}

void    ft_free_parent(t_pipex *pipex)
{
    close_pipes(pipex);
    ft_free2(pipex->path_list);
}

void    ft_free_child(t_pipex *pipex)
{
    ft_free2(pipex->cmd_args);
    free(pipex->cmd);
}

void    setup_child2_redirection(t_pipex pipex)
{
    close(pipex.end[1]); // close write-end
    dup2(pipex.outfile, STDOUT_FILENO); // redirect output to outfile a.k.a outfile = stdout
    close(pipex.outfile); // close outfile fd
    dup2(pipex.end[0], STDIN_FILENO); // redirect input to read-end a.k.a read-end = stdin
    close(pipex.end[0]); // close read-end
}

void    setup_child1_redirection(t_pipex pipex)
{
    close(pipex.end[0]);  // close read-end
    dup2(pipex.infile, STDIN_FILENO);// redirect input to infile a.k.a infile = stdin
    close(pipex.infile); // close infile fd
    dup2(pipex.end[1], STDOUT_FILENO); // redirect output to write-end a.k.a write-end = stdout
    close(pipex.end[1]); // close write-end fd
}

char    **get_cmd_args(char *command)
{
    char *cmd;
    char **cmd_args;

    cmd = ft_strtrim(command, " ");
    if (!cmd[0])
    {
        free(cmd);
        ft_perror(command);  
    }
    cmd_args = ft_split(cmd, ' '); 
    free(cmd);
    return (cmd_args);
}

void    child1_process(char **av, char **env, t_pipex pipex)
{
    pipex.infile = open_infile(av[1], pipex.end);
    setup_child1_redirection(pipex);
    pipex.cmd_args = get_cmd_args(av[2]);
    pipex.cmd = get_cmd_path(pipex.path_list, av[2]);
    if (!pipex.cmd)
    {
        ft_free_child(&pipex);
        ft_cerror(ERR_CMD);
        exit(128);
    }
    execve(pipex.cmd, pipex.cmd_args, env);
}

void    child2_process(char **av, char **env, t_pipex pipex)
{
    pipex.outfile = open_outfile(av[4], pipex.end);
    setup_child2_redirection(pipex);
    pipex.cmd_args = get_cmd_args(av[3]);
    pipex.cmd = get_cmd_path(pipex.path_list, av[3]);
    if (!pipex.cmd)
    {
        ft_free_child(&pipex);
        ft_cerror(ERR_CMD);
        exit(128);
    }
    execve(pipex.cmd, pipex.cmd_args, env);
}