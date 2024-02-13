/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m3ayz00 <m3ayz00@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 01:20:40 by m3ayz00           #+#    #+#             */
/*   Updated: 2024/02/13 22:44:38 by m3ayz00          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_full_path(char **paths, char *cmd)
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

void    free_parent(t_pipex *pipex)
{
    close(pipex->end[0]);
    close(pipex->end[1]);
    close(pipex->infile);
    close(pipex->outfile);
    ft_free2(pipex->path_list);
}

void    free_child(t_pipex *pipex)
{
    ft_free2(pipex->cmd_args);
    free(pipex->cmd);
}


void    child1_process(char **av, char **env, t_pipex pipex)
{
    close(pipex.end[0]);
    dup2(pipex.infile, STDIN_FILENO);
    dup2(pipex.end[1], STDOUT_FILENO);
    pipex.cmd_args = ft_split(av[2], ' ');
    pipex.cmd = get_full_path(pipex.path_list, pipex.cmd_args[0]);
    if (!pipex.cmd)
    {
        free_child(&pipex);
        ft_cerror(ERR_CMD);
        exit(1);
    }
    execve(pipex.cmd, pipex.cmd_args, env);
}

void    child2_process(char **av, char **env, t_pipex pipex)
{
    close(pipex.end[1]);
    dup2(pipex.outfile, STDOUT_FILENO);
    dup2(pipex.end[0], STDIN_FILENO);
    pipex.cmd_args = ft_split(av[3], ' ');
    pipex.cmd = get_full_path(pipex.path_list, pipex.cmd_args[0]);
    if (!pipex.cmd)
    {
        free_child(&pipex);
        ft_cerror(ERR_CMD);
        exit(1);
    }
    execve(pipex.cmd, pipex.cmd_args, env);
}