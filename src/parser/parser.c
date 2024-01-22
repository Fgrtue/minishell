/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/08 14:37:24 by jiajchen      #+#    #+#                 */
/*   Updated: 2024/01/19 17:25:09 by jiajchen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	(*fill_builtin(t_cmd *cmd))(t_cmd* cmd, char ***env, t_global* global)
{
	if (!cmd->args || !(cmd->args)[0])
		return (NULL);
	if (!ft_strncmp((cmd->args)[0], "echo", ft_strlen((cmd->args)[0])))
		return (*ft_echo);
	if (!ft_strncmp((cmd->args)[0], "cd", ft_strlen((cmd->args)[0])))
		return (*ft_cd);
	if (!ft_strncmp((cmd->args)[0], "pwd", ft_strlen((cmd->args)[0])))
		return (&ft_pwd);
	if (!ft_strncmp((cmd->args)[0], "export", ft_strlen((cmd->args)[0])))
		return (&ft_export);
	if (!ft_strncmp((cmd->args)[0], "unset", ft_strlen((cmd->args)[0])))
		return (&ft_unset);
	if (!ft_strncmp((cmd->args)[0], "env", ft_strlen((cmd->args)[0])))
		return (&ft_env);
	if (!ft_strncmp((cmd->args)[0], "exit", ft_strlen((cmd->args)[0])))
		return (&ft_exit);
	return (NULL);
}

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

// t_cmd	*get_cmds(t_lexer **lst, t_lexer *lexer)
int	get_cmds(t_global* global)
{
	t_cmd	*cur;
	t_lexer *lexer;
	
	lexer = global->lexer;
	while (lexer)
	{
		cur = ft_cmdnew();
		if (cur == NULL)
			return(ft_error(global, "malloc failed", 0)); //todo: error handler
		if (lexer->token == PIPE_LINE)
		{
			fill_redir(&(global->lexer), lexer->next, cur);
			lexer = lexer->next;
		}
		else
		{
			fill_redir(&(global->lexer), lexer, cur);
			lexer = global->lexer;
		}
		lexer = fill_cmd_args(lexer, cur, args_size(lexer));
		cur->builtin = fill_builtin(cur);
		ft_cmdaddback(&global->cmds, cur);
	}
	return (0);
}
