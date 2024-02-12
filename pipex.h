/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m3ayz00 <m3ayz00@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:30:17 by msaadidi          #+#    #+#             */
/*   Updated: 2024/02/12 02:37:28 by m3ayz00          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include <stdint.h>

char	**ft_split(char const *s, char c);
char    *first_word(char *str);
char	*ft_strtrim(char *s, char *set);
void	*ft_calloc(size_t num_elements, size_t element_size);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int     ft_strlen(char *str);
int	    ft_memcmp(const void *str1, const void *str2, size_t n);

void    ft_perror(char *err);
void    check_args(int ac, char **av);
char    **get_full_path(char *cmd1, char *cmd2, char **env);
char    **get_cmd_path(char  **av, char **envp);
void    child_process(char **av, char **env, int p[]);
void    parent_process(char **av, char **env, int p[]);
void    ft_free2(char **path_list);

#endif