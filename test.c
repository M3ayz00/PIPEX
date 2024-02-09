#include <string.h>
#include <unistd.h>
#include "pipex.h"

char    *ft_strjoin(char *str1, char *str2)
{
    if (!str1)
        return (str2);
    if (!str2)
        return (str1);
    int full_len = strlen(str1) + strlen(str2);
    char *joined = malloc(full_len + 1);
    strcpy(joined, str1);
    strcpy(joined + strlen(str1), str2);
    joined[full_len] = '\0';
    return joined;
}

int main(int ac, char **av, char **env)
{
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
        char **cmd_args = ft_split(av[2], ' '); // split command and options
        if(execve("/bin/ls", cmd_args, env) == -1) // execute cmd with options
            perror("Error1");
        close(p1[1]); // close write-end
    }
    else
    {
        wait(NULL); // wait for child process to die
        close(p1[1]); // close write-end 
        dup2(fd2, 1); // redirect output to outfile a.k.a outfile = stdout
        dup2(p1[0], 0); // redirect input to read-end a.k.a read-end = stdin
        char **cmd_args = ft_split(av[3], ' '); // split command and options
        if(execve("/usr/bin/wc", cmd_args, env) == -1) // execute cmd with options
            perror("Error2");
        close(p1[0]); // close read-end
        return 0;
    }
}