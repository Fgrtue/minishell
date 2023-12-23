/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/20 14:53:03 by jiajchen      #+#    #+#                 */
/*   Updated: 2023/12/23 13:57:31 by kkopnev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char** create_env(char** envp)
{
    int i;
    int j;
    char** env;

    i = -1;
    j = -1;
    if (!envp)
        return (NULL);
    while(envp[++i])
        continue;
    env = malloc(sizeof(char *) * (i + 2));
    while(++j < i)    
        env[j] = ft_strdup(envp[j]);
    env[j] = NULL;
    return (env); 
}

int	check_quotes(char *str)
{
    int	i;

    i = -1;
    if (!str)
        return (0);
    while(str[++i])
    {
        if (str[i] == '\"')
        {
            while(str[++i] && str[i] != '\"')
                continue;
            if (!str[i])
                return (0);
        }
        else if (str[i] == '\'')
        {
            while(str[++i] && str[i] != '\'')
                continue;
            if (!str[i])
                return (0);
        }
    }
    return (1);
}
