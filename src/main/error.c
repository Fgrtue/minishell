/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/29 17:03:26 by jiajchen      #+#    #+#                 */
/*   Updated: 2024/01/19 17:14:51 by jiajchen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


/* Function sets exit code to 1, writes an error message and returns a ptr */
void*	ft_error_nvoid(t_global* global, char* error_msg)
{
	global->exit_c = 1;
	errno = EPERM;
	perror(error_msg);
	return (NULL);
}

/* Function sets exit code to 1, writes an error message and returns nothing */
int	ft_error(t_global* global, char* error_msg, int exit_c)
{
	global->exit_c = exit_c;
	if (errno && error_msg)
		perror(error_msg);
	else
		ft_putendl_fd(error_msg, 2);
	return (1);
}

void	ft_unlink(t_cmd *cmds)
{
	while(cmds)
	{
		if (cmds->heredoc && !access(cmds->heredoc, F_OK))
			unlink(cmds->heredoc);
		cmds = cmds->next;
	}
}

/* 
	Function prints an error message, if there is one, is case of here_doc mode
	it unlinks all the hererdocs, and then cleans all the commands + lexer. Finally
	depending on the mode it either cleans environment or not.
 */
void	free_global(char *msg, t_global *global, int clean_env)
{
	if (!global)
		return ;
	if (errno && msg)
		perror(msg);
	else if (msg)
		ft_putendl_fd(msg, STDERR_FILENO);
	if (global->here_doc_exit != 0)
		ft_unlink(global->cmds);
	if (global->cmds)
		ft_cmdclean(global->cmds);
	if (global->lexer)
		ft_lexclean(global->lexer);
	if (clean_env == 1 && global->env)
		free_arr(global->env);
}