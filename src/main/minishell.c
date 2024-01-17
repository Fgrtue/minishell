/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/07 16:11:54 by jiajchen      #+#    #+#                 */
/*   Updated: 2024/01/17 20:56:40 by kkopnev       ########   odam.nl         */
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

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_global	*global;
	// int			exit_c; // GS
	// char		**env; // GS
	// t_lexer		*lex;  // GS
	// t_cmd		*cmds;  // GS
	
	argv = NULL; // unused parameter
	argc = 0; // unsused parameter
	global = malloc(sizeof(t_global));
	if (!global)
		return (1);
	// exit_c = 0; // GS->exit_c = 0;
	global->exit_c = 0;
	global->here_doc = 0;
	// env = create_env(envp); // GS->env = create_env(envp);
	global->env = create_env(envp);
	while (1)
	{
		free_global(NULL, global, 0); // clean it if it's non empty;
		// line = ft_readline(env);
		line = ft_readline(global);
		// lex = ft_lexer(line); // GS->lex = ft_lexer(line);
		global->lexer = ft_lexer(line);
		// expand_env(&lex, env, exit_c); // expand_env(&(GS->lex), GS->env, GS->exit_c);
		expand_env(global);
		if (global->exit_c == 1)
			continue ; 
		global->cmds = get_cmds(global); // GS->cmds = get_cmds(&(GS->lex), lex);
		if (global->exit_c == 1)
			continue ; 
		// ft_lexclean(lex); // WHY LEX CLEAN IS HERE??
		global->exit_c = executor(global); // GS->exit_c = executor(GS->cmds, GS->env);
		// ft_cmdclean(cmds); // ft_GSclean(GS);
		free(line);
	}
    free_arr(global->env); //QESTION:: in what case do we get to these lines?
	free(global);
	return (0);
}
