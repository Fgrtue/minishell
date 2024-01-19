/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkopnev <kkopnev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/17 15:39:55 by jiajchen      #+#    #+#                 */
/*   Updated: 2024/01/16 20:30:48 by kkopnev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Ctrl+C sends SIGINT, Ctrl+\ sends SIGQUIT, and Ctrl+Q sends SIGCONT.
 * 
 * ctrl-c: interrupt child process and continue to next iteration of while loop. 
 * 			exit_code = 130
 * ctrl-d: interrupt all child processes and exit shell
 * ctrl-\: interrupt child process if ther is any. if it is in child process exit_c=131
*/

static volatile sig_atomic_t	g_sig;

void	interrupt_exe(int sig)
{
	if (sig == SIGINT)
	{
		kill(0, sig);
	}
	if (sig == SIGQUIT)
	{
		write(STDOUT_FILENO, "Quit\n", 5);
	}
	g_sig = sig;
}

void	interrupt_read(int sig)
{
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	interrupt_heredoc(int sig)
{
	ioctl(0, TIOCSTI, "\n"); //still don't quite understand what is does
	exit(130);
}

void	signals_handler(t_mode mode)
{
	if (mode == INTERACTIVE) //in readline
	{
		signal(SIGINT, interrupt_read);
		signal(SIGQUIT, SIG_IGN); // Why here we have an integer? Why do we have two lines here?
	}
	if (mode == NON_INTERACTIVE) // in executor
	{
		signal(SIGINT, interrupt_exe);
		signal(SIGQUIT, interrupt_exe);
	}
	if (mode == HEREDOC) //sigquit wont affect
	{
		signal(SIGINT, interrupt_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
}

/* do not use mode*/

// volatile sig_atomic_t g_sig;

// void	interrupt_interactive(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		write(STDOUT_FILENO, "\n", 1);
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 	}
// 	g_sig = sig;
// }

// void	interrupt_execute(int sig)
// {
// 	if (sig == SIGINT)
// 		kill(0, sig);
// 	g_sig = sig;
// }

// void	interrupt_heredoc(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		ioctl(0, TIOCSTI, "\n");
// 		exit(130);
// 	}
// 	g_sig = sig;
// }

// void	signals_handler(__sighandler_t sighandle)
// {
// 	g_sig = 0;
// 	signal(SIGINT, sighandle);
// 	signal(SIGQUIT, sighandle);
// }