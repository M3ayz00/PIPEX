/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:30:14 by msaadidi          #+#    #+#             */
/*   Updated: 2024/02/17 15:49:42 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_c_in_set(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	wait_and_return_status(int pid1, int pid2)
{
	int	wstatus;
	int	exit;

	exit = 0;
	waitpid(pid1, &wstatus, 0);
	if (WEXITSTATUS(wstatus) == 1)
		exit++;
	waitpid(pid2, &wstatus, 0);
	if (WEXITSTATUS(wstatus) == 1)
		exit++;
	return (exit);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (ac != 5)
		return (ft_cerror(ERR_INPUT));
	pipex.infile = open(av[1], O_RDONLY);
	if (pipex.infile < 0)
		ft_perror(ERR_INFILE);
	pipex.outfile = open(av[4], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (pipex.outfile < 0)
		ft_perror(ERR_OUTFILE);
	if (pipe(pipex.end) == -1)
		ft_perror(ERR_PIPE);
	pipex.path_list = get_path_list(envp);
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		child1_process(av, envp, pipex);
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		child2_process(av, envp, pipex);
	free_parent(&pipex);
	return (wait_and_return_status(pipex.pid1, pipex.pid2));
}
