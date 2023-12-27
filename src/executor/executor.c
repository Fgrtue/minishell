/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/18 15:05:45 by jiajchen      #+#    #+#                 */
/*   Updated: 2023/12/27 11:48:43 by jiajchen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_wait(t_cmd* cmd)
{
	int	status;
	
	while(cmd->next)
	{
		waitpid(cmd->pid, NULL, 0);
		cmd = cmd->next;
	}
	waitpid(cmd->pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_SUCCESS);
}

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
	return (NULL);
}

void	execute_cmd(t_cmd *cmd, char **env)
{
	char	*path;
	
	dup2((cmd->fd_io)[0], STDIN_FILENO);
	dup2((cmd->fd_io)[1], STDOUT_FILENO);
	close_fd(cmd->fd_io);
	if (!cmd->args)
		exit(EXIT_SUCCESS);
	if (cmd->builtin != NULL) // check whether the command is builtin.
		exit(cmd->builtin(cmd, env));
	path = get_path((cmd->args)[0], env);
	if (path)
		execve(path, cmd->args, env);
	else
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd((cmd->args)[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit(127); //is this saved?
	}
}

void	process_cmd(t_cmd *cmd, char **env)
{
	int	exit_c; // result of the execution in the builtin.
	int	inf;
	
	cmd->pid = fork(); // fork for the child proccess
	if (cmd->pid == -1)
		perror("Fork"); // exit
	if (cmd->pid == 0) // part for the child proccess
	{
		execute_cmd(cmd, env);
	}
	else
		close_fd(cmd->fd_io); // in case of the parent process close all the files.
}

void pipe_exe(t_cmd* cmd, char** env)
{
	int	fd[2];
	
	while (cmd)
	{
		if (cmd->next && pipe(fd) == -1) //do we need pipe if it is the last command
			perror("Pipe");
		if (cmd->next)
			(cmd->fd_io)[1] = fd[1];
		check_redirection(cmd); // inside command we have fd_io[2] where we write the input and output of the command. This function changes these values if needed.
		process_cmd(cmd, env);
		if (cmd->next) 
			(cmd->next->fd_io)[0] = fd[0];
		cmd = cmd->next;
	}
}
	
void	executor(t_cmd *cmd, char **env)
{
	int	exit_c;
	
	if (!cmd->next && cmd->builtin)
	{
		check_redirection(cmd); 
		exit_c = cmd->builtin(cmd, env);
	}
	else
	{
		pipe_exe(cmd, env);
		exit_c = ft_wait(cmd);
	}
}
