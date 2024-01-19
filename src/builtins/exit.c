/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkopnev <kkopnev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/22 16:44:19 by kkopnev       #+#    #+#                 */
/*   Updated: 2024/01/17 13:15:57 by kkopnev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*

    Exit the shell, returning a status of n to the shell’s parent. 
    If n is omitted, the exit status is that of the last command executed. 
    Any trap on EXIT is executed before the shell terminates. 

*/

static int	ft_isnumb(char *str)
{
	if (!str)
		return (0);
	if (*str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

// int ft_exit(t_cmd* cmd, char ***env)
int ft_exit(t_global*	global)
{
	global->exit_c = 0;
	// (void) env; // why do we need that?
    write(STDOUT_FILENO, "exit\n", 5);
	if (!global->cmds || !((global->cmds)->args[1]))
		global->exit_c = 0; // why do we keep it 0?
	else if (!ft_isnumb((global->cmds)->args[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd((global->cmds)->args[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	}
    else if ((global->cmds)->args[2])
    {
        ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		if (ft_isnumb((global->cmds)->args[1]))
        	return (1);
    }
    else
        global->exit_c = ft_atoi((global->cmds)->args[1]);
	// free_lex_exit(...)
	// free_cmd_exit(NULL, global->cmds, &(global->env), global->exit_c);
	// free_global(global);
    return (global->exit_c);
}

// exit abc
// exit
// bash: exit: abc: numeric argument required

// exit 1 2
// not exit
// exit
// bash: exit: too many arguments

// exit abd abd