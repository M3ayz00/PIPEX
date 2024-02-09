/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:30:17 by msaadidi          #+#    #+#             */
/*   Updated: 2024/02/09 16:56:00 by msaadidi         ###   ########.fr       */
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

void    check_args(int ac, char **av);
char	**ft_split(char const *s, char c);
char    *is_cmd_valid(char *cmd, char **env);
char	**ft_free(char **str, size_t n);
char    *first_word(char *str);
char	*ft_strtrim(char *s, char *set);
void	*ft_calloc(size_t num_elements, size_t element_size);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int     ft_strlen(char *str);
int	    ft_memcmp(const void *str1, const void *str2, size_t n);

#endif