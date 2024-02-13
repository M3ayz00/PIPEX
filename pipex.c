/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:30:14 by msaadidi          #+#    #+#             */
/*   Updated: 2024/02/13 17:24:11 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int ac, char **av, char **envp)
{
    t_pipex pipex;

    if (ac != 5)
        ft_cerror(ERR_INPUT);
    check_args(ac, av);
    if (pipe(pipex.end)== -1)
        ft_perror(ERR_PIPE);
    pipex.path_list = get_path_list(envp);
    pipex.pid1 = fork();
    if (pipex.pid1 == -1)
        ft_perror(ERR_FORK);
    else if (pipex.pid1 == 0)
        child1_process(av, envp, pipex);
    waitpid(pipex.pid1, NULL, 0);
    pipex.pid2 = fork();
    if (pipex.pid2 == -1)
        ft_perror(ERR_FORK);
    else if (pipex.pid2 == 0)
        child2_process(av, envp, pipex);
    ft_free_parent(&pipex);
    waitpid(pipex.pid2, NULL, 0);
    return (0);
}
