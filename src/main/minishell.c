/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/07 16:11:54 by jiajchen      #+#    #+#                 */
/*   Updated: 2023/12/27 20:29:06 by kkopnev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int sign = 0;

void print_lex(t_lexer* lexer)
{
    printf("################################\n");
    while(lexer)
    {
        printf("LEXER: %p\n", lexer);
        printf("################################\n");
        printf("content:%s\n", lexer->content);
        printf("len: %i\n", lexer->len);
        printf("token: %i\n", lexer->token);
        printf("state: %i\n", lexer->state);
        printf("prev: %p\n", lexer->prev);
        printf("next: %p\n", lexer->next);
        printf("################################\n");
        lexer = lexer->next;
    }
	printf("################################\n");
}

void print_args(char** args)
{
    int i = 0;
    
    printf("The content:\n");
    while(args && args[i])
    {
        printf("    %d. %s\n", i, args[i]);
        i++;
    }
}

void print_cmd(t_cmd* cmd)
{
    printf("************************************\n");
    while(cmd)
    {
        printf("CMD: %p\n", cmd);
        printf("************************************\n");
        print_args(cmd->args);
        printf("The num of redir: %d\n", cmd->num_redir);
        printf("\nRedir: %p\n", cmd->redir);
		print_lex(cmd->redir);
        printf("\nprev: %p\n", cmd->prev);
        printf("next: %p\n", cmd->next);
        printf("************************************\n");
        cmd = cmd->next;
    }
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	int		exit_c;
	t_lexer*	lexer;
	char**		env;
	t_cmd	*cmds;
	
    if (signal(SIGINT, handl_ctrlc) == SIG_ERR)
	{
        perror("Cntr+C: ");
        return 1;
    }
    if (signal(SIGQUIT, handl_ctrld) == SIG_ERR)
	{
        perror("Ctrl+D: ");
        return 1;
    }
	env = create_env(envp);
	while (1)
	{
		sign = 1;
		line = readline("minishell: ");
		if (!line) 
            exit(0);
		sign = 0;
		if (line && !*line)
			continue;
		if (line && *line)
			add_history(line);
		if (!check_quotes(line))
		{
			perror("Wrong quotes");
			continue;
		} 				
		lexer = ft_lexer(line);
		expand_env(&lexer, env, exit_c);
		polish_lex(&lexer);
		cmds = get_cmds(&lexer, lexer);
		executor(cmds, env);
		ft_lexclean(&lexer);
		ft_cmdclean(&cmds);
	}
	free_arr(env);
	return (0);
}
