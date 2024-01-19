/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/07 16:11:54 by jiajchen      #+#    #+#                 */
/*   Updated: 2024/01/19 17:34:01 by jiajchen      ########   odam.nl         */
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

void reset_global(t_global* global)
{
	ft_unlink(global->cmds);
	if (global->cmds)
		ft_cmdclean(global->cmds);
	if (global->lexer)
		ft_lexclean(global->lexer);
	if (g_sig == SIGINT)
		global->exit_c = 130;
	else if (g_sig == SIGQUIT)
		global->exit_c = 131;
}

int	main(int argc, char **argv, char **envp)
{
	char			*line;
	static t_global	global;

	global.env = create_env(envp);
	while (argc && argv)
	{
		reset_global(&global);
		line = ft_readline(&global);
		global.lexer = ft_lexer(line);
		if (expand_env(&global))
			continue;
		if (get_cmds(&global))
			continue ; 
		global.exit_c = executor(&global); 
		free(line);
	}
	return (0);
}
