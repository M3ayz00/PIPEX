/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:37:21 by msaadidi          #+#    #+#             */
/*   Updated: 2024/02/07 20:08:12 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    check_args(int ac, char **av)
{
    if (ac != 5)
    {
        perror("Error");
        exit(1);
    }
    if (access(av[1], F_OK) == -1)
    {
        perror("Error");
        exit(1);
    }
    if (!av[2][0] || !av[3][0])
    {
        perror("Error");
        exit(1);
    }
}