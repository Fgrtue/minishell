/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/07 16:11:54 by jiajchen      #+#    #+#                 */
/*   Updated: 2023/12/20 18:20:20 by kkopnev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*line;
	int		exit_status;
	t_lexer*	lexer;
	
	exit_status = 0;
	while (1)
	{
		line = readline("minishell:");
		if (!line || !*line)
			continue;
		// TO DO: error control
		if (line && *line )
			add_history(line);
		if (!check_quotes(line)) // TO Do: check if the quotes are closed
		//	write(:didn't clode the quotes);
		//	continue;						
		// LEXER PART
		// lexer = ft_lexer(line);
		// protection
		// expander(lexer, env, exit status);
		// parser = ft_parser(lexer, env);
		// executor(parser, env, exit_status);
		// cleaner(lexer, parser);
	}
}