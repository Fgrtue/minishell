/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkopnev <kkopnev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/22 16:36:50 by kkopnev       #+#    #+#                 */
/*   Updated: 2024/01/17 20:38:33 by kkopnev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


int ft_env(t_cmd* cmd, char ***env, t_global* global)
{
    int     i;
    char    **env_tmp;

    i = -1;
    global = NULL;
    env_tmp = *env;
    while(env[++i])
    {
        if (ft_strchr(env_tmp[i], '=') != NULL)
            ft_putendl_fd(env_tmp[i], (cmd->fd_io)[1]);
    }
    return (0);
}