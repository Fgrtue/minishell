/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/18 15:05:45 by jiajchen      #+#    #+#                 */
/*   Updated: 2023/12/20 14:55:23 by jiajchen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


// 1. if there is redir inf = redir in; outf = redir out;
// 1.1 if '<<' inf = the new file user types
// 1.2 if '>>'
// 2. inf = stdin(if it is the first cmd)or fd[0](not first cmd)
// 3. outf = fd[1](if not the last cmd) or stdout(if it is the last cmd)

// 1. if there is no argument, 

// if there is one cmd, parent process; else, chile process
// if cmd is not found, exit(127)
// TO CHECK: how to do with 'bin/cat file1' in path match


/*
pipe_exe

 	1.	Check for redirections in a separate function that returns 
		the file descriptions for the input and output. If no input/output
		is specified, then you put the pippw in input/output variables 
	2.	Then we get into the while loop that will be running until we reach the
		last command. We also write down the process id into the struct that we 
		work with. 
	3.	First open the pipe, and check the fd returned by redir function. If any of
		then are filled, use them instead of a pipe. Else use the pipe.
	4.	Proceed to function process_cmd(), plugging in arguments, env, inf, outf
	5.	Inside it we check: a) That args is not empty; b) For the builtins (whether the command that we have in args[0]
		is a builtin) -- if the command is a path to a builtin. If it is, then we 
		poceed to the function and execute it. If
		its not, then we find a path to the command and then run it using dup, execve;
	6. In the end we wait for the processes with id written down in the struct,
		in other words we go through the linked list again and wait for every
		process id written down in there.

how the redirection func should work?

	1. If it is normal > or <, then take the last redir 
		check the unlink
		check the order or redir

how the builtins should work?

how the wait function should wait?
*/	
		
	
void	executor(t_cmd *cmd, char **env)
{
	int	fd[2];

	if (!cmd->next)
		simple_exe(cmd, env);
	else
		pipe_exe(cmd, env);
	while (cmd)
	{

		if (cmd->next && pipe(fd) != -1)
			process_cmd(cmd, env, fd);
			
	}
}

/**
 * 
 * 1. if the command name contains no slashes, we locate it
 * 2. if 
*/