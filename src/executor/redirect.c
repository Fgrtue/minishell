/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/20 15:15:43 by jiajchen      #+#    #+#                 */
/*   Updated: 2023/12/20 17:32:41 by jiajchen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	check_redirection(t_cmd *cmd)
{
	t_lexer	*redir;
	char 	*inf;
	char 	*outf;
	int		in;
	int		out;

	redir = cmd->redir;
	while (redir)
	{
		if (redir->token == REDIR_IN)
		{
			inf = redir->next->content;
			cmd->hd = 0;
		}
		if (redir->token == REDIR_OUT || redir->token == DREDIR_OUT)
			outf = redir->next->content;
		if (redir->token == HERE_DOC)//
		{
			inf = redir->next->content;
			cmd->hd = 1;
		}
		redir = redir->next->next;
	}
	in = open(inf, O_RDONLY);
	
}