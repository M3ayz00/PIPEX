#include <string.h>
#include <unistd.h>
#include "pipex.h"


char    *find_path(char **env)
{
    while (ft_memcmp(*env, "PATH=", 5) != 0)
        env++;
    return ((*env) + 5);
}

int main(int ac, char **av, char **env)
{
    t_pipex pipex;
    pipex.infile = open(av[1], O_RDONLY);
    pipex.outfile = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
    pipe(pipex.end);
    pipex.pid1 = fork();
    if (pipex.pid1 == 0)
    {
        // Child process
        close(pipex.end[0]);  // Close read-end
        dup2(pipex.infile, 0); // redirect input to infile a.k.a infile = stdin
        dup2(pipex.end[1], 1); // redirect output to write-end a.k.a write-end = stdout
        pipex.cmd_args = ft_split(av[2], ' '); // split command and options
        if(execve("/bin/ls", pipex.cmd_args, env) == -1) // execute cmd with options
            perror("Error1");
        close(pipex.end[1]); // close write-end
    }
    else
    {
        pipex.pid2 = fork();
        if (pipex.pid2 == 0)
        {
            close(pipex.end[1]); // close write-end 
            dup2(pipex.outfile, 1); // redirect output to outfile a.k.a outfile = stdout
            dup2(pipex.end[0], 0); // redirect input to read-end a.k.a read-end = stdin
            pipex.cmd_args = ft_split(av[3], ' '); // split command and options
            if(execve("/usr/bin/wc", pipex.cmd_args, env) == -1) // execute cmd with options
                perror("Error2");
            close(pipex.end[0]); // close read-end
        }
        else
        {
            wait(NULL); // wait for child process to die
        }
    }
}