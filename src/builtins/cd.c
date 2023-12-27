/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/22 15:30:29 by jiajchen      #+#    #+#                 */
/*   Updated: 2023/12/27 18:53:45 by jiajchen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


/**
 *  cd or cd ~ : cd HOME
 *  cd / : cd root directory
 *  cd .. : go to last direct of PWD
 *  cd ../.
 *  cd ../minishell/../minishell
 *  cd ~/Documents/../Documents/
 * 	cd - : change the dir to OLDPWD
 *  PWD=/home/jiajchen/Documents
 * change PWD and OLDPWD
*/

/* return the index or pointer?????????? will be easier*/
int	ft_find_key(char *var, char **env)
{
	int	i;
	char* new_var;

	i = 0;
	new_var = ft_strjoin(var, "="); //not free original var
	while (env[i] && ft_strncmp(env[i], new_var, ft_strlen(new_var)) != 0)
		i++;
	free(new_var);
	if (env[i])
		return (i);
	return (-1);
}

void	ft_move_env(char **env, char **tmp, int pos)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (tmp[++j])
	{
		if (j == pos)
			i++;
		else
		{
			env[i] = tmp[j];
			i++;
		}
	}
}

/* str is malloced for env, should not be freed */
char	**ft_change_env(char *var, char *str, char **env)
{
	char	*tmp_str;
	char	**tmp;
	int		i;
	int		size;

	i = ft_find_key(var, env);
	if (i != -1)
	{
		tmp_str = env[i];
		env[i] = str;
		free(tmp_str);
		return (env);
	}
	tmp = env;
	size = get_env_size(env) + 1;
	env = ft_calloc(size + 1, sizeof(char *));
	if (!env)
		perror("malloc"); // DO ERROR
	ft_move_env(env, tmp, size);
	env[size - 1] = str;
	env[size] = NULL;
	free(tmp);
	return (env);
}

/* dir is not malloced */
char	*expand_dir(t_cmd *cmd, char *dir, char **env)
{
	char	*new;
	
	if (!dir)
		new = find_variable("HOME", env, 0);
	else if (dir[0] == '~')
		new = ft_strjoin_free(find_variable("HOME", env, 0), dir + 1);
	else if (dir[0] == '-' && !dir[1])
	{
		new = find_variable("OLDPWD", env, 0);
		ft_putendl_fd(new, (cmd->fd_io)[1]);
	}
	else
		new = ft_strdup(dir);
	return (new);
}

int	ft_cd(t_cmd *cmd, char ***env)
{
	char	*dir;
	char	*ptr;
	char	pwd[1024];

	if ((cmd->args)[2])
	{
		ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	dir = expand_dir(cmd, (cmd->args)[1], *env);
	ft_print_exp(cmd, *env);
	if (chdir(dir) == -1)
	{
		free(dir);
		perror((cmd->args)[1]); // TO DO: error() (cmd->args)[1] could be NULL !protection!
		return (EXIT_FAILURE);
	}
	ptr = (*env)[ft_find_key("PWD", *env)] + 4;
	*env = ft_change_env("OLDPWD", ft_strjoin("OLDPWD=", ptr), *env);
	*env = ft_change_env("PWD", ft_strjoin("PWD=", getcwd(pwd, sizeof(pwd))), *env);
	free(dir);
	return (EXIT_SUCCESS);
}
