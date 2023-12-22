/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/22 15:30:29 by jiajchen      #+#    #+#                 */
/*   Updated: 2023/12/22 17:52:08 by jiajchen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


/**
 *  cd / cd ~ : cd HOME
 *  cd .. : go to last direct of PWD
 *  cd ../.
 *  cd ../minishell/../minishell
 *  PWD=/home/jiajchen/Documents
 * change PWD and OLDPWD
*/



int	ft_cd(t_cmd *cmd, char **env)
{
	char	*home;

	if ((cmd->args)[])
	// home = find_variable("HOME", env, 0);
	// pwd = find_variable("PWD", env ,0);
	// 
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	char pwd[1024];

	getcwd(pwd, sizeof(pwd));
	printf("%s\n", pwd);
	char *dir = "~/Documents/minishell";
	chdir(dir);
	getcwd(pwd, sizeof(pwd));
	printf("%s\n", pwd);
	while(1)
		continue;
}