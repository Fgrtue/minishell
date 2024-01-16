/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/07 16:11:54 by jiajchen      #+#    #+#                 */
/*   Updated: 2024/01/16 12:37:56 by kkopnev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_readline(char **env)
{
	char	*prompt;
	char	*line;

	prompt = ft_strdup("minishell:");
	prompt = ft_strjoin_free_d(prompt, find_variable("PWD", env, 0));
	prompt = ft_strjoin_free(prompt, "$ ");
	signals_handler(interrupt_interactive);
	line = readline(prompt);
	free(prompt);
	if (line == NULL)
	{
		rl_clear_history();
		ft_exit(NULL, &env);
	}
	if (line && *line)
		add_history(line);
	if (!check_quotes(line))
	{
		ft_putendl_fd("minishell: wrong quotes!", STDERR_FILENO);
		free(line);
		line = ft_readline(env);
	}
	return (line);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	int			exit_c;
	char		**env;
	t_lexer		*lex;
	t_cmd		*cmds;
	
	exit_c = 0;
	env = create_env(envp);
	while (1)
	{
		line = ft_readline(env);
		lex = ft_lexer(line);
		expand_env(&lex, env, exit_c);
		cmds = get_cmds(&lex, lex);
		ft_lexclean(lex);
		exit_c = executor(cmds, env);
		ft_cmdclean(cmds);
		free(line);
	}
    free_arr(env);
	return (0);
}
