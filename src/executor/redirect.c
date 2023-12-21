/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/20 15:15:43 by jiajchen      #+#    #+#                 */
/*   Updated: 2023/12/21 17:52:03 by jiajchen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* 

	in case of a redirection we have to close the previous file for input/output
	in ft_io, and open a different file. 

	in case if we encounter a here_doc redirection we go to 
	a function here_doc.  
	
	
	
	, we start reading lines
	and check wheather we encounter a delimiter that was provided to us.
	once we find a delimiter -- we finish reading, save the file and then proceed
	to the command.

*/

int here_doc(t_cmd*	cmd, char* inf)
{
	char*	line;
	
	if (cmd->here_doc != -1)
		close(cmd->here_doc);
	cmd->here_doc = open(inf, O_RDWR| O_CREAT | O_TRUNC, 0644);
	// unlink(inf);
	line = readline("heredoc: ");
	while (ft_strncmp(line, inf, ft_strlen(inf)) != 0)
	{
		write(cmd->here_doc, line, ft_strlen(line));
		write(cmd->here_doc, "\n", 1);
		free(line);
		line = readline("heredoc: ");
	}
	free(line);
	return (1);
}

char*	redir_in(t_cmd*	cmd, t_lexer* redir)
{
	if (redir->token == REDIR_IN)
	{
		cmd->hd_bool = 0;
		return(redir->next->content);
	}
	else if (redir->token == HERE_DOC)
	{
		cmd->hd_bool = here_doc(cmd, redir->next->content);
		return(redir->next->content);
	}
	else
		return (NULL);
}

char*	redir_out(t_cmd*	cmd, t_lexer* redir)
{
	if (redir->token == REDIR_OUT)
	{ 
		cmd->dr_bool = 0;
		return(redir->next->content);
	}
	else if (redir->token == DREDIR_OUT)
	{
		cmd->dr_bool = 1;
		return(redir->next->content);
	}
	else
		return (NULL);
}

void set_redir(t_cmd* cmd, char* inf, char* outf)
{
	// close the pipe if needed
	if (inf && (cmd->fd_io)[0] != 0)
		close((cmd->fd_io)[0]);
	if (outf && (cmd->fd_io)[1] != 1)
		close((cmd->fd_io)[0]);
	printf("inf: %s\noutf: %s\n", inf, outf);
	//set new fd
	if (outf && cmd->dr_bool == 1)
		(cmd->fd_io)[1] = open(outf, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (outf && cmd->dr_bool == 0)
		(cmd->fd_io)[1] = open(outf, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (inf && cmd->hd_bool == 1)
	{
		close(cmd->here_doc);
		cmd->here_doc = open(inf, O_RDONLY);
		unlink(inf);
		(cmd->fd_io)[0] = cmd->here_doc;
	}
	else if (inf && cmd->hd_bool == 0)
		(cmd->fd_io)[0] = open(inf, O_RDONLY);
	// check open error
	if ((cmd->fd_io)[1] == -1)
		perror(outf); //To DO
	if ((cmd->fd_io)[0] == -1)
		perror(inf); //To DO
}

void	check_redirection(t_cmd *cmd)
{
	t_lexer	*redir;
	char	*inf;
	char	*outf;

	inf = NULL;
	outf = NULL;
	redir = cmd->redir;
	while (redir)
	{
		if (redir->token == REDIR_IN || redir->token == HERE_DOC)
			inf = redir_in(cmd, redir);
		if (redir->token == REDIR_OUT || redir->token == DREDIR_OUT)
			outf = redir_out(cmd, redir);
		redir = redir->next->next;
	}
	set_redir(cmd, inf, outf);
}