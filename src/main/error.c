/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/29 17:03:26 by jiajchen      #+#    #+#                 */
/*   Updated: 2023/12/31 13:25:17 by jiajchen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"



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