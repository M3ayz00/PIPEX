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
    int fd = open(av[1], O_RDWR);
    int fd2 = open(av[4], O_RDWR | O_CREAT | O_TRUNC);
    dup2(fd2, 1);
    int p1[2], p2[2];
    pipe(p1);
    pipe(p2);
    int pid = fork();
    if (pid == 0)
    {
        char **cmd_args = ft_split(av[2], ' ');
        if(execve("/bin/ls", cmd_args, env) == -1)
            perror("Error");
    }
    else
    {
        wait(NULL);
        
        return 0;
    }
}