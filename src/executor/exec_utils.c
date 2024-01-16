/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkopnev <kkopnev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/20 21:08:21 by kkopnev       #+#    #+#                 */
/*   Updated: 2024/01/02 14:13:21 by jiajchen      ########   odam.nl         */
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

int	ft_wait(t_cmd* cmd)
{
	int	status;
	
	while (cmd->next)
	{
		errno = 0;
		while (waitpid(cmd->pid, NULL, 0) == -1 && errno == EINTR)
			errno = 0;
		cmd = cmd->next;
	}
	while (waitpid(cmd->pid, &status, 0) == -1 && errno == EINTR)
			errno = 0;;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (WTERMSIG(status));
	return (EXIT_SUCCESS);
}
