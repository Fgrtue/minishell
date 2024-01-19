/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/22 15:31:20 by jiajchen      #+#    #+#                 */
/*   Updated: 2024/01/17 20:42:26 by kkopnev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <linux/limits.h>

int	ft_pwd(t_cmd* cmd, char ***env, t_global* global)
{
	char	dir[PATH_MAX];

	(void) env;
	global = NULL;
	if (getcwd(dir, sizeof(dir)) == NULL)
	{
		perror("minishell: pwd: ");
		return (EXIT_FAILURE);
	}
	ft_putendl_fd(dir, (cmd->fd_io)[1]);
	return (EXIT_SUCCESS);
}
