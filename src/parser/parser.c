/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/08 14:37:24 by jiajchen      #+#    #+#                 */
/*   Updated: 2023/12/21 16:41:45 by jiajchen      ########   odam.nl         */
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
		i++;
	}
	cmd->args[size] = NULL;
	return (lexer);
}

void	fill_redir(t_lexer **lst, t_lexer *lexer, t_cmd *cmd)
{
	while (lexer && lexer->token != PIPE_LINE)
	{
		if (lexer->token == REDIR_IN || lexer->token == REDIR_OUT \
			|| lexer->token == HERE_DOC || lexer->token == DREDIR_OUT)
		{
			if (lexer->prev != NULL)
			{
				lexer = lexer->prev;
				ft_lexaddback(&(cmd->redir), ft_lexretract(lst, lexer->next));
				ft_lexaddback(&(cmd->redir), ft_lexretract(lst, lexer->next));
				lexer = lexer->next;
			}
			else
			{
				ft_lexaddback(&(cmd->redir), ft_lexretract(lst, *lst));
				ft_lexaddback(&(cmd->redir), ft_lexretract(lst, *lst));
				lexer = *lst;
			}
			cmd->num_redir++;
		}
		else
			lexer = lexer->next;
	}
}

int	args_size(t_lexer *lexer)
{
	int	size;

	size = 0;
	while (lexer && lexer->token != PIPE_LINE)
	{
		size++;
		lexer = lexer->next;
	}
	return (size);
}
	
t_cmd	*get_cmds(t_lexer **lst, t_lexer *lexer)
{
	t_cmd 	*cmd;
	t_cmd	*cur;
	
	cmd = NULL;
	while (lexer)
	{
		cur = ft_cmdnew();
		if (lexer->token == PIPE_LINE)
		{
			fill_redir(lst, lexer->next, cur);
			lexer = lexer->next;
		}
		else
		{
			fill_redir(lst, lexer, cur);
			lexer = *lst;
		}
		lexer = fill_cmd_args(lexer, cur, args_size(lexer));
		// fill_builtin();
		ft_cmdaddback(&cmd, cur);
	}
	return (cmd);
}