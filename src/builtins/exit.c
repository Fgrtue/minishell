/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkopnev <kkopnev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/22 16:44:19 by kkopnev       #+#    #+#                 */
/*   Updated: 2023/12/22 18:43:25 by kkopnev       ########   odam.nl         */
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
	int	answ;
	int	flag;

	answ = 1;
	flag = 0;
	if (!str)
		return (0);
	if (*str == '-')
		str++;
	while (*str)
	{
		if (ft_isdigit(*str))
			answ *= 1;
		str++;
	}
	return (answ);
}

int ft_exit(t_cmd* cmd)
{
    if (!ft_isnumb((cmd->args)[1]))
        perror("(cmd->args)[1])): ");
    if ((cmd->args)[1] && cmd->args[2])
    {
        perror("exit: ");
        write(STDIN_FILENO, "exit\n", 5);
        return (1);
    }
    if (ft_isnumb((cmd->args)[1]))
        exit(ft_atoi((cmd->args)[1]));
    //TO DO: free everything
    exit(0);
}