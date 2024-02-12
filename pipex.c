/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:30:14 by msaadidi          #+#    #+#             */
/*   Updated: 2024/02/12 19:21:50 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int ac, char **av, char **envp)
{
    int p1[2];
    check_args(ac, av);
    if (pipe(p1)== -1)
        ft_perror("pipe");
    int pid1 = fork();
    if (pid1 == -1)
        ft_perror("fork");
    else if (pid1 == 0)
        child1_process(av, envp, p1);
    int pid2 = fork();
    if (pid2 == -1)
        ft_perror("fork");
    else if (pid2 == 0)
        child2_process(av, envp, p1);
    int wstatus;
    waitpid(-1, &wstatus, 0);
        if(WEXITSTATUS(wstatus) == 1)
            return (1);
    // waitpid(pid2, &wstatus, 0);
    return (0);
}
