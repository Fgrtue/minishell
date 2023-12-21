/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/18 15:05:45 by jiajchen      #+#    #+#                 */
/*   Updated: 2023/12/20 22:40:40 by kkopnev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void ft_wait(t_cmd* cmd)
{
	while(cmd)
	{
		waitpid(cmd->pid, NULL, 0);
		cmd = cmd->next;
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
		check_redirection(cmd); // inside command we have fd_io[2] where we
								// write the input and output of the command. This function changes these values if needed.
		printf("Redirections are %d %d\n", (cmd->fd_io)[0], (cmd->fd_io)[1]);
		if (cmd->builtin != NULL) // check whether the command is builtin.
			exit_c = cmd->builtin(cmd); 
		// run_cmd(cmd, env);
	}
	else
		close_fd(cmd->fd_io); // in case of the parent process close all the files.
}

void simple_exe(t_cmd*	cmd, char** env)
{
	int	exit_c;
	
	printf("We got here!\n");
	check_redirection(cmd);
	printf("Redirections are %d %d\n", (cmd->fd_io)[0], (cmd->fd_io)[1]);
	if (cmd->builtin != NULL)
		exit_c = cmd->builtin(cmd); 
	printf("We didn't get here\n");
	//	3. execute the command
}

void pipe_exe(t_cmd* cmd, char** env)
{
	int	fd[2];
	
	while (cmd)
	{
		if (pipe(fd) == -1)
			perror("Pipe");
		if (cmd->next)
			(cmd->next->fd_io)[1] = fd[1];
		process_cmd(cmd, env);
		if (cmd->next) 
			(cmd->next->fd_io)[0] = fd[0];
		cmd = cmd->next;
	}
}
	
void	executor(t_cmd *cmd, char **env)
{
	if (!cmd->next)
	{
		simple_exe(cmd, env);
	}
	else
	{
		pipe_exe(cmd, env);
		ft_wait(cmd);
	}
}



/**
 * 
 * 1. if the command name contains no slashes, we locate it
 * 2. if 
*/