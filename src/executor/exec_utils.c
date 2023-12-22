/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkopnev <kkopnev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/20 21:08:21 by kkopnev       #+#    #+#                 */
/*   Updated: 2023/12/22 09:42:49 by kkopnev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

void close_fd(int fd[])
{
    if (fd[0] != 0)
        close(fd[0]);
    if (fd[1] != 1)
        close(fd[1]);
}