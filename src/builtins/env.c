/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkopnev <kkopnev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/22 16:36:50 by kkopnev       #+#    #+#                 */
/*   Updated: 2023/12/23 13:46:59 by kkopnev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_env(t_cmd* cmd, char** env)
{
    int i;

    i = -1;
    while(env[++i])
    {
        write((cmd->fd_io)[1], env[i], ft_strlen(env[i]));
        write((cmd->fd_io)[1], "\n", 1);
    }
    return (0);
}