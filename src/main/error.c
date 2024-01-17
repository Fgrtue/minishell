/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/29 17:03:26 by jiajchen      #+#    #+#                 */
/*   Updated: 2024/01/17 18:56:00 by kkopnev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


/* Function sets exit code to 1, writes an error message and returns a ptr */
void*	ft_error_nvoid(t_global* global, char*	error_msg)
{
	global->exit_c = 1;
	errno = EPERM;
	perror(error_msg);
	return (NULL);
}

/* Function sets exit code to 1, writes an error message and returns nothing */
void	ft_error_void(t_global* global, char*	error_msg)
{
	global->exit_c = 1;
	errno = EPERM;
	perror(error_msg);
}

void	ft_unlink(t_cmd *cmds)
{
	while(cmds)
	{
		if (cmds->heredoc)
			unlink(cmds->heredoc);
		cmds = cmds->prev;
	}
}

/* 
	Function prints an error message, if there is one, is case of here_doc mode
	it unlinks all the hererdocs, and then cleans all the commands + lexer. Finally
	depending on the mode it either cleans environment or not.
 */
void	free_global(char *msg, t_global *global, int clean_env)
{
	if (errno && msg)
		perror(msg);
	else if (msg)
		ft_putendl_fd(msg, STDERR_FILENO);
	if (global->here_doc == 1)
		ft_unlink(global->cmds);
	if (global->cmds)
		ft_cmdclean(global->cmds);
	if (global->lexer)
		ft_lexclean(global->lexer);
	if (clean_env == 1 && global->env)
		free_arr(global->env);
}