/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/18 15:05:45 by jiajchen      #+#    #+#                 */
/*   Updated: 2024/01/02 18:17:34 by jiajchen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


char	*get_path(char *cmd, char **env)
{
	char	**patharr;
	char	*path;
	int		i;

	if (cmd && access(cmd, F_OK) == 0)
		return (cmd);
	i = 0;
	while (ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	patharr = ft_split(env[i] + 5, ':');
	i = -1;
	while (patharr[++i])
	{
		path = ft_strjoin(patharr[i], "/");
		path = ft_strjoin_free(path, cmd);
		if (access(path, F_OK) == 0)
		{
			free_arr(patharr);
			return (path);
		}
		free(path);
	}
	free_arr(patharr);
	return (NULL);
}

void	execute_cmd(t_cmd *cmd, char **env)
{
	char	*path;
	
	if (check_redirection(cmd))
		exit(1);
	dup2((cmd->fd_io)[0], STDIN_FILENO);
	dup2((cmd->fd_io)[1], STDOUT_FILENO);
	close_fd(cmd->fd_io);
	if (!cmd->args[0])
		exit(EXIT_SUCCESS);
	if (cmd->builtin != NULL)
		exit(cmd->builtin(cmd, &env));
	path = get_path((cmd->args)[0], env);
	if (path)
		execve(path, cmd->args, env);
	else
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd((cmd->args)[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit(127);
	}
}

void	process_cmd(t_cmd *cmd, char **env)
{
	int	exit_c;
	int	inf;
	
	cmd->pid = fork();
	if (cmd->pid == -1)
		free_cmd_exit("Fork", cmd, env, 1);
	if (cmd->pid == 0)
	{
		execute_cmd(cmd, env);
	}
	else
		close_fd(cmd->fd_io);
}

int pipe_exe(t_cmd* cmd, char** env)
{
	int	fd[2];
	
	while (cmd)
	{
		if (cmd->next && pipe(fd) == -1)
			free_cmd_exit("Pipe", cmd, env, 1);
		if (cmd->next)
			(cmd->fd_io)[1] = fd[1];
		check_redirection(cmd);
		process_cmd(cmd, env);
		if (cmd->next) 
			(cmd->next->fd_io)[0] = fd[0];
		cmd = cmd->next;
	}
	return (0);
}
	
int	executor(t_cmd *cmd, char **env)
{
	int	exit_c;
	
	if (!cmd)
		return (0);
	// create_heredoc(cmd);
	if (g_sig != 0)
		return (130);
	signals_handler(interrupt_execute);
	if (!cmd->next && cmd->builtin)
	{
		if (check_redirection(cmd))
			return (EXIT_FAILURE);
		exit_c = cmd->builtin(cmd, &env);
	}
	else
	{
		pipe_exe(cmd, env);
		exit_c = ft_wait(cmd);
	}
	return exit_c;
}
