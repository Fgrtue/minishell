/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/07 16:11:54 by jiajchen      #+#    #+#                 */
/*   Updated: 2024/01/18 12:23:51 by kkopnev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_readline(t_global *global)
{
	char	*prompt;
	char	*line;

	prompt = ft_strdup("minishell:");
	prompt = ft_strjoin_free_d(prompt, find_variable("PWD", global->env, 0));
	prompt = ft_strjoin_free(prompt, "$ ");
	signals_handler(INTERACTIVE);
	line = readline(prompt);
	free(prompt);
	if (line == NULL)
	{
		rl_clear_history();
		ft_exit(global->cmds, &(global->env), global);
	}
	if (line && *line)
		add_history(line);
	if (!check_quotes(line))
	{
		ft_putendl_fd("minishell: wrong quotes!", STDERR_FILENO);
		free(line);
		line = ft_readline(global);
	}
	return (line);
}

// /* when execute */
// int	check_signal(int exit_c)
// {
// 	if (g_sig == SIGINT)
// 		return (130);
// 	if (g_sig == SIGQUIT)
// 		return (131);
// 	return (exit_c);
// }
void ft_set_global(t_global* global)
{
	global->here_doc_exit = 0;
	global->lexer = NULL;
	global->cmds = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_global	*global;
	argv = NULL; // unused parameter
	global = malloc(sizeof(t_global));
	if (!global)
		return (1);
	global->exit_c = 0;
	ft_set_global(global);
	global->env = create_env(envp);
	while (1)
	{
		if (argc == -1)
		{
			free_global(NULL, global, 0); // clean it if it's non empty;
			ft_set_global(global);
		}
		argc = -1;
		line = ft_readline(global);
		global->lexer = ft_lexer(line);
		expand_env(global);
		if (global->exit_c == 1)
			continue ; 
		global->cmds = get_cmds(global); 
		if (global->exit_c == 1)
			continue ; 
		global->exit_c = executor(global); 
		free(line);
	}
    free_arr(global->env); //QESTION:: in what case do we get to these lines?
	free(global);
	return (0);
}
