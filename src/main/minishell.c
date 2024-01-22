/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/07 16:11:54 by jiajchen      #+#    #+#                 */
/*   Updated: 2024/01/22 14:40:59 by jiajchen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_readline(t_global *global)
{
	char	*prompt;
	char	*line;

	prompt = ft_strdup("minishell:");
	prompt = ft_strjoin_free_d(prompt, find_variable("PWD", global));
	prompt = ft_strjoin_free(prompt, "$ ");
	signals_handler(INTERACTIVE);
	line = readline(prompt);
	free(prompt);
	if (line == NULL)
	{
		rl_clear_history();
		ft_exit(NULL, global);
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

int	main(int argc, char **argv, char **envp)
{
	char			*line;
	static t_global	global;

	global.env = create_env(envp);
	while (argc && argv)
	{
		line = ft_readline(&global);
		free_global(&global);
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
