/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkopnev <kkopnev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/20 21:08:21 by kkopnev       #+#    #+#                 */
/*   Updated: 2024/01/22 16:11:55 by jiajchen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	here_doc(char *heredoc, char *inf)
{
	char	*line;
	int		hd;

	hd = open(heredoc, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (hd == -1)
	{
		perror("heredoc");
		return ;
	}
	line = readline("heredoc: ");
	while (line && (!*line || ft_strncmp(line, inf, ft_strlen(line)) != 0))
	{
		ft_putendl_fd(line, hd);
		free(line);
		line = readline("heredoc: ");
	}
	if (line == NULL)
		ft_putendl_fd("minishell: warning: delimited by EOF", 2);
	else
		free(line);
	close(hd);
}

void	close_fd(int fd[])
{
	if (fd[0] != 0)
		close(fd[0]);
	if (fd[1] != 1)
		close(fd[1]);
}

int	ft_wait(t_cmd *cmd)
{
	int	status;

	while (cmd->next)
	{
		errno = 0;
		while (waitpid(cmd->pid, NULL, 0) == -1 && errno == EINTR)
			errno = 0;
		cmd = cmd->next;
	}
	errno = 0;
	while (waitpid(cmd->pid, &status, 0) == -1 && errno == EINTR)
		errno = 0;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (WTERMSIG(status));
	return (EXIT_SUCCESS);
}
