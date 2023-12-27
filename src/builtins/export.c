/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkopnev <kkopnev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/23 14:37:22 by kkopnev       #+#    #+#                 */
/*   Updated: 2023/12/27 14:27:11 by kkopnev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_print_exp(t_cmd* cmd, char** env)
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

int ft_export(t_cmd* cmd, char** env)
{
    int i;
    long int len;
    char*   ptr_eq;
    char*   key;
    char**  tmp_env;

    i = 0;
    tmp_env = env;
    if (!(cmd->args)[++i])
        return (ft_print_exp(cmd ,env));
    else
    {
        while((cmd->args)[i])
        {
            len = ft_strchr((cmd->args)[i], '=') - (cmd->args)[i];
            key = ft_calloc(len + 1, sizeof(char));
            if (key == NULL)
                return (127); // PROTECT
            ft_memcpy(key, (cmd->args)[i], len);
            env = ft_change_env(key, ft_strdup((cmd->args)[i]), tmp_env);
            if (env == NULL)
                return (127); // PROTECT
            // free_env(tmp_env)  ADD FUNCTION;
            free(key);
            key = NULL;
        }
    }
    return (0);    
}

/*

EXPORT

    WITHOUT ARGUMENTS

        Output: key="vale" pairs (NOTE: dquotes!). If the value was exported
        in the single quotes, then any metacaracter is preceeded with the '\'
        sign. If it was exported in double quotes, then everuthing is expanded.

        IN FACT we could output just env in alphabetical order. 

    WITH ARGUMENTS

        0. Search for all the arguments that are of the shape key=value.
        value can be:
            a. word
            b. env variable
            c. string in double quotes
            d. string in single quotes
        key can be:
            a. word
            b. env variable (only one!)
        i.e. key cannot be something that consists of several
        elements (either separated with the space or in the quotes
        with spaces)
        1. If the value is in dquotes -- expand env variables and unite
        all of the elements in the quotes
        2. If the value is in single quotes -- don't expand the env variables
        and unite everything together
        3. If the value is an env variable -- expand it
        4, If it is a word -- leave it like that
        5. Once you obtained a string, just add key=value (expanded key and value)
        to the environment in the bottom

*/