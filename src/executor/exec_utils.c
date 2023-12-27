/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkopnev <kkopnev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/20 21:08:21 by kkopnev       #+#    #+#                 */
/*   Updated: 2023/12/27 11:44:31 by jiajchen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

void	close_fd(int fd[])
{
	if (fd[0] != 0)
		close(fd[0]);
	if (fd[1] != 1)
		close(fd[1]);
}   
