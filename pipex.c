/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m3ayz00 <m3ayz00@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:30:14 by msaadidi          #+#    #+#             */
/*   Updated: 2024/02/10 22:26:22 by m3ayz00          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int ac, char **av, char **envp)
{
    int p1[2];
    check_files(ac, av);
    // check_cmds(av[2], av[3], envp);
    if (pipe(p1)== -1)
    {
        perror("Error");
        exit(1);
    }
    int pid = fork();
    if (pid == -1)
    {
        perror("Fork");
        exit(1);
    }
    else if (pid == 0)
        child_process(av, envp, p1);
    else
    {
        int wstatus;
     // wait for child process to die
        waitpid(-1, &wstatus, 0);
        if(WIFEXITED(wstatus))
            parent_process(av, envp, p1);
    }
    return (0);
}
