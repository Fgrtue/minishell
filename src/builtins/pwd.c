/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/22 15:31:20 by jiajchen      #+#    #+#                 */
/*   Updated: 2023/12/27 18:00:56 by jiajchen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <linux/limits.h>

int	ft_pwd(t_cmd *cmd, char ***env)
{
	char	dir[PATH_MAX];

	(void) env;
	if (getcwd(dir, sizeof(dir)) == NULL)
	{
		perror("minishell: pwd: ");
		return (EXIT_FAILURE);
	}
	ft_putendl_fd(dir, (cmd->fd_io)[1]);
	return (EXIT_SUCCESS);
}
