/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m3ayz00 <m3ayz00@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:30:14 by msaadidi          #+#    #+#             */
/*   Updated: 2024/02/13 22:37:04 by m3ayz00          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int ac, char **av, char **envp)
{
    t_pipex pipex;

    if (ac != 5)
        return(ft_cerror(ERR_INPUT));
    pipex.infile = open(av[1], O_RDONLY);
    if (pipex.infile < 0)
        ft_perror(ERR_INFILE);
    pipex.outfile = open(av[4], O_TRUNC | O_CREAT | O_RDWR, 0644);
    if (pipex.outfile < 0)
        ft_perror(ERR_OUTFILE);
    if (pipe(pipex.end)== -1)
        ft_perror(ERR_PIPE);
    pipex.path_list = get_path_list(envp);
    pipex.pid1 = fork();
    if (pipex.pid1 == 0)
        child1_process(av, envp, pipex);
    pipex.pid2 = fork();
    if (pipex.pid2 == 0)
        child2_process(av, envp, pipex);
    free_parent(&pipex);
    waitpid(pipex.pid1, NULL, 0);
    waitpid(pipex.pid2, NULL, 0);
    return (0);
}
