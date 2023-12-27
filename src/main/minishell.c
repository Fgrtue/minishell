/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/07 16:11:54 by jiajchen      #+#    #+#                 */
/*   Updated: 2023/12/27 19:01:07 by kkopnev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	int		exit_c;
	t_lexer*	lexer;
	char**		env;
	t_cmd	*cmds;
	
    if (signal(SIGINT, handleCtrlC) == SIG_ERR)
	{
        perror("Cntr+C: ");
        return 1;
    }
    if (signal(SIGQUIT, handleCtrlD) == SIG_ERR)
	{
        perror("Ctrl+D: ");
        return 1;
    }
	env = create_env(envp);
	while (1)
	{
		sig = 1;
		line = readline("minishell: ");
		if (!line) 
            exit(0);
		sig = 0;
		if (line && !*line)
			continue;
		if (line && *line )
			add_history(line);
		if (!check_quotes(line))
		{
			perror("Wrong quotes\n");
			continue;
		} 				
		lexer = ft_lexer(line);
		expand_env(&lexer, env, exit_c);
		polish_lex(&lexer);
		cmds = get_cmds(&lexer, lexer);
    	ft_export(cmds, env);
		ft_lexclean(&lexer);
		ft_cmdclean(&cmds);
	}
	return (0);
}
