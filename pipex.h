/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:30:17 by msaadidi          #+#    #+#             */
/*   Updated: 2024/02/17 15:44:33 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include <stdint.h>

# define ERR_INFILE "Infile"
# define ERR_OUTFILE "Outfile"
# define ERR_INPUT "Invalid number of arguments.\n"
# define ERR_PIPE "Pipe"
# define ERR_CMD "command not found\n"

typedef struct s_pipex
{
	int		pid1;
	int		pid2;
	int		infile;
	int		outfile;
	int		end[2];
	char	**path_list;
	char	*cmd;
	char	**cmd_args;
}	t_pipex;

char	**ft_split(char const *s, char *set);
void	*ft_calloc(size_t num_elements, size_t element_size);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int		ft_strlen(char *str);
int		ft_memcmp(const void *str1, const void *str2, size_t n);
char	*ft_strjoin(char *s1, char *s2);
int		ft_wordcount(char const *s, char *set);
int		is_c_in_set(char c, char *set);

void	free_parent(t_pipex *pipex);
void	ft_free2(char **path_list);
int		ft_cerror(char *err);
void	ft_perror(char *err);
char	**get_path_list(char **env);
void	child1_process(char **av, char **env, t_pipex pipex);
void	child2_process(char **av, char **env, t_pipex pipex);

#endif
