/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 10:28:30 by jiajchen      #+#    #+#                 */
/*   Updated: 2024/01/18 17:52:07 by kkopnev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd*	ft_cmdnew(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->args = NULL;
    cmd->builtin = NULL;
    cmd->num_redir = 0;
    (cmd->fd_io)[0] = 0;
    (cmd->fd_io)[1] = 1;
    cmd->dr_bool = 0;
    cmd->heredoc = NULL;
	cmd->redir= NULL;
    cmd->prev = NULL;
    cmd->next = NULL;
	return (cmd);
}

void	ft_cmdaddfront(t_cmd** cmd, t_cmd* new)
{
    if (new == NULL)
    {
        return ;
    }
	new->next = *cmd;
    if (*cmd != NULL)
    {
        (*cmd)->prev = new;
    }
	*cmd = new;
}

void	ft_cmdaddback(t_cmd **cmd, t_cmd *new)
{
    t_cmd* last;

    last = NULL;
	if ((*cmd) == NULL)
		ft_cmdaddfront(cmd, new);
	else
    {
        last = ft_cmdlast(*cmd);
		last->next = new;
        new->prev = last; 
        new->next = NULL;
    }
}

t_cmd*	ft_cmdlast(t_cmd* cmd)
{
	if (cmd == NULL)
		return (NULL);
	while (cmd->next != NULL)
		cmd = cmd->next;
	return (cmd);
}

void	ft_cmddel(t_cmd* node)
{
    if (node->redir)
    {
        ft_lexclean(node->redir);
    }
    if (node->args)
    {
        free_arr(node->args); 
    }
    if (node->heredoc)
    {
        free(node->heredoc);  
    }
    free(node);
}

/* change to *cmd clean from the beginning */
void    ft_cmdclean(t_cmd *cmd)
{
    t_cmd*    temp;
    
    temp = NULL;
    while (cmd && cmd->prev)
        cmd = cmd->prev;
    while(cmd)
    {   
        temp = cmd;
        cmd = cmd->next;
        if (temp)
        {
            ft_cmddel(temp);
            temp = NULL;
        }
    }
}