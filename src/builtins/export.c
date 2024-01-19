/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkopnev <kkopnev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/23 14:37:22 by kkopnev       #+#    #+#                 */
/*   Updated: 2024/01/19 17:02:00 by jiajchen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_print_exp(t_cmd* cmd, char **env)
{
	int	i;

	i = -1;
	while(env[++i])
	{
		write((cmd->fd_io)[1], env[i], ft_strlen(env[i]));
		write((cmd->fd_io)[1], "\n", 1);
	}
	return (0);
}

int ft_export(t_cmd* cmd, char ***env, t_global* global)
{
	int		i;
	int		len;
	char	*ptr_eq;
	char	*key;

    i = 0;
    if (!(cmd->args)[1])
        return (ft_print_exp(cmd, *env));
    while((cmd->args)[++i])
    {
        ptr_eq = ft_strchr((cmd->args)[i], '=');
        if(!ptr_eq && ft_find_key((cmd->args)[i], *env) != -1) //key already in 
            continue;
        if (!ptr_eq)
            len = ft_strlen((cmd->args)[i]);
        else
            len = ptr_eq - (cmd->args)[i];
        key = ft_calloc(len + 1, sizeof(char));
        if (key == NULL)
            return (127); // PROTECT
        ft_memcpy(key, (cmd->args)[i], len);
        global->env = ft_change_env(key, ft_strdup((cmd->args)[i]), *env);
        free(key);
    }
    return (0);    
}
