/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:30:14 by msaadidi          #+#    #+#             */
/*   Updated: 2024/02/09 17:24:02 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int ac, char **av, char **env)
{
    check_args(ac, av);
    char *cmd1_path = is_cmd_valid(first_word(av[2]), env);
    if (!cmd1_path)
    {
        perror("Error3");
        free(cmd1_path);
        exit(1);
    }
    char *cmd2_path = is_cmd_valid(first_word(av[3]), env);
    if (!cmd2_path)
    {
        perror("Error4");
        free(cmd2_path);
        exit(1);
    }
    char *cmd1 = ft_strtrim(av[2], " ");
    char *cmd2 = ft_strtrim(av[3], " ");
    int fd = open(av[1], O_RDONLY);
    int fd2 = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
    int p1[2];
    pipe(p1);
    int pid = fork();
    if (pid == 0)
    {
        // Child process
        close(p1[0]);  // Close read-end
        dup2(fd, 0); // redirect input to infile a.k.a infile = stdin
        dup2(p1[1], 1); // redirect output to write-end a.k.a write-end = stdout
        char **cmd_args = ft_split(cmd1, ' '); // split command and options
        if(execve(cmd1_path, cmd_args, env) == -1) // execute cmd with options
            perror("Error1");
        close(p1[1]); // close write-end
    }
    else
    {
        wait(NULL); // wait for child process to die
        close(p1[1]); // close write-end 
        dup2(fd2, 1); // redirect output to outfile a.k.a outfile = stdout
        dup2(p1[0], 0); // redirect input to read-end a.k.a read-end = stdin
        char **cmd_args = ft_split(cmd2, ' '); // split command and options
        if(execve(cmd2_path, cmd_args, env) == -1) // execute cmd with options
            perror("Error2");
        close(p1[0]); // close read-end
        return 0;
    }
}
