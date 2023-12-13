/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/08 14:37:24 by jiajchen      #+#    #+#                 */
/*   Updated: 2023/12/13 17:36:02 by kkopnev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_lexer	*fill_cmd_args(t_lexer *lexer, t_cmd *cmd, int size)
{
	int	i;
	
	cmd->args = ft_calloc(sizeof(char *), size + 1);
	if (cmd->args == NULL)
		perror("malloc"); // todo: error()
	i = 0;
	while (lexer && lexer->token != PIPE_LINE)
	{
		cmd->args[i] = ft_strdup(lexer->content);
		if (!cmd->args[i])
			perror("malloc");
		lexer = lexer->next;
	}
	cmd->args[size] = NULL;
	return (lexer);
}

t_lexer	*fill_cmd(t_lexer **lst, t_lexer *lexer, t_cmd *cmd)
{
	int		cmd_len;
	
	cmd_len = 0;
	while (lexer && lexer->token != PIPE_LINE)
	{
		if (lexer->token == REDIR_IN || lexer->token == REDIR_OUT \
			|| lexer->token == HERE_DOC || lexer->token == DREDIR_OUT)
		{
			lexer = lexer->next->next;
			ft_lexaddback(&(cmd->redir), ft_lexretract(lst, lexer->prev->prev));
			ft_lexaddback(&(cmd->redir), ft_lexretract(lst, lexer->prev));
			cmd->redir++;
		}
		else
		{
			lexer = lexer->next;
			cmd_len++;
		}
	}
	while (!(lexer->prev) && lexer->prev->token != PIPE_LINE)
		lexer = lexer->prev;
	lexer = fill_cmd_args(lexer, cmd, cmd_len);
	return (lexer);
}

t_cmd	*get_cmds(t_lexer **lst, t_lexer *lexer)
{
	t_cmd 	*cmd;
	t_cmd	*cur;
	
	cmd = NULL;
	while (lexer)
	{
		if (lexer->token == PIPE_LINE)
			lexer = lexer->next;
		cur = ft_cmdnew();
		lexer = fill_cmd(lst, lexer, cur);
		ft_cmdaddback(&cmd, ft_cmdnew());
	}
	ft_lexclean(lst);
	return (cmd);
}

/**
 * There will be two functions:
 * 
 * 1. Fills the redirections
 * 2. Fills the arguments
 * 
 * The first one retreives all the redirections until the first encountered pipe
 * Moving the redirections (<, >, <<, >>) to the t_lexer linked list in the 
 * t_cmd struct
 * 
 * The second one retreives all the commands into 2D array (args) skipping the spaces
 * inbetween the nodes, and in case when it finds a quoted part it creates one
 * string out of everything that is inside the quotes and puts it into argc. 
 * 
 * INPUT: t_lexer (which is the LL)
 * OUTPUT: t_cmd (which is also a LL)
 * 
 * ALGORITHM:
 * 
 * We need a pointer that will be used for lexering the beggning of new iteration.
 * It will be updated when we finish with the part unting the closest pipe or NULL.
 * First we allocate the memory for the current t_cmd. Then we use two functions 
 * 
 *  ft_redir -- uses and changes the t_lexer LL and adds redirection nodes to t_cmd
 * 
 * 	ft_fill_args -- uses t_lexer to fill the t_cmd. It should return the pointer to
 * 	the closest pipe (or NULL). 
 * 
 *	We update our pointer with the new value returned by ft_fill_args, and add the
	created node to the Linked List of commands.
 * 
 * 	ft_redir:
 * 
 * 	takes to t_lexer and t_cmd
 *	Goes through the t_lexer until the first pipe

	If it sees a node with REDIR_OUT/REDIR_IN/HERE_DOC/DREDIR_OUT in GENERAL STATE
	then it adds a value to the number of redir and adds this node to the redir in 
	t_cmd as a redirection. 
	After that it takes the second element and adds this to the redir in t_cmd.

	Now we have tha updated Lexer. Function returns the count var.

	ft_fill_args:
	
		takes t_cmd and allocates the amount of memory for the lenght of the LL until
		the pipe (or NULL), and then fills 2D array one by one 
		terminating it with NULL.
*/