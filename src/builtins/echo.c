/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkopnev <kkopnev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/22 10:36:14 by kkopnev       #+#    #+#                 */
/*   Updated: 2024/01/17 20:38:15 by kkopnev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*

	Output the args, separated by spaces, terminated with a newline. 
	The return status is 0 unless a write error occurs. 
	If -n is specified, the trailing newline is suppressed. 
	If the -e option is given, interpretation of the following 
	backslash-escaped characters is enabled. 
	The -E option disables the interpretation of these escape characters, 
	even on systems where they are interpreted by default. 
	The xpg_echo shell option may be used to dynamically determine 
	whether or not echo expands these escape characters by default. 
	echo does not interpret -- to mean the end of options. 

*/

int ft_echo(t_cmd* cmd, char ***env, t_global* global)
{
	int     mode;
	int     i;
	char*   line;

	(void) env;
	global = NULL;
	i = 1;
	mode = 0;
	line = NULL;
	if ((cmd->args)[1]) 
	{
		mode = ft_strncmp((cmd->args)[1], "-n", ft_strlen((cmd->args)[1]));
		if (mode == 0)
			i++;
		while ((cmd->args)[i])
		{
			line = ft_strjoin_free(line, (cmd->args)[i++]);
			if ((cmd->args)[i])
				line = ft_strjoin_free(line, " ");
		}
		write((cmd->fd_io)[1], line, ft_strlen(line));
	}
	if (mode != 0)
		write((cmd->fd_io)[1], "\n", 1);
	free(line);
	return (0);
}
