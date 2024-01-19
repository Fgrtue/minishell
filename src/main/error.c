/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/29 17:03:26 by jiajchen      #+#    #+#                 */
/*   Updated: 2024/01/17 14:55:39 by kkopnev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_set_err(t_global *global)
{
	global->err = 1;
}

t_cmd*	ft_error_nv(t_global* global, char*	error_msg)
{
	ft_set_err(global);
	errno = EPERM;
	perror(error_msg);
	return (NULL);
}

void	ft_error_void(t_global* global, char*	error_msg)
{
	ft_set_err(global);
	errno = EPERM;
	perror(error_msg);
}

void	free_cmd_exit(char *msg, t_cmd *cmd, char **env, int ec)
{
	if (errno && msg)
		perror(msg);
	else if (msg)
		ft_putendl_fd(msg, STDERR_FILENO);
	if (cmd)
		ft_cmdclean(cmd);
	if (env)
		free_arr(env);
	exit(ec);
}