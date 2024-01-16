/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/20 15:15:43 by jiajchen      #+#    #+#                 */
/*   Updated: 2024/01/16 12:36:58 by kkopnev       ########   odam.nl         */
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

char	*here_doc(t_cmd *cmd, char *inf)
{
	char*	line;
	int		hd;

	hd = open(cmd->heredoc, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (hd == -1)
	{
		perror("heredoc");
		return (NULL);
	}
	signals_handler(interrupt_heredoc);
	line = readline("heredoc: ");
	while (line && (!*line || ft_strncmp(line, inf, ft_strlen(line)) != 0))
	{
		ft_putendl_fd(line, hd);
		free(line);
		sign = 2;
		line = readline("heredoc: ");
		sign = 0;
	}
	if (line == NULL)
		ft_putendl_fd("minishell: warning: delimited by EOF", 2);
	else
		free(line);
	close(hd);
	return (cmd->heredoc);
}

char*	redir_out(t_cmd *cmd, t_lexer *redir)
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

/* return 1 if there is error */
int set_redir(t_cmd *cmd, char *inf, char *outf)
{
	if (inf && (cmd->fd_io)[0] != 0)
		close((cmd->fd_io)[0]);
	if (outf && (cmd->fd_io)[1] != 1)
		close((cmd->fd_io)[1]);
	if (outf && cmd->dr_bool == 1)
		(cmd->fd_io)[1] = open(outf, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (outf && cmd->dr_bool == 0)
		(cmd->fd_io)[1] = open(outf, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (inf)
		(cmd->fd_io)[0] = open(inf, O_RDONLY);
	if ((cmd->fd_io)[1] == -1)
		perror(outf);
	if ((cmd->fd_io)[0] == -1)
		perror(inf);
	if (access(cmd->heredoc, F_OK) == 0)
		unlink(cmd->heredoc);
	if ((cmd->fd_io)[0] == -1 || (cmd->fd_io)[1] == -1)
		return (1);
	return (0);
}

/* if error return 1 */
int	check_redirection(t_cmd *cmd)
{
	t_lexer	*redir;
	char	*inf;
	char	*outf;
	static int	hd;

	inf = NULL;
	outf = NULL;
	redir = cmd->redir;
	cmd->heredoc = ft_itoa(++hd);
	while (redir)
	{
		errno = 0;
		if (redir->token == REDIR_IN && !access(redir->next->content, R_OK))
			inf = redir->next->content;
		if (redir->token == HERE_DOC) //&& !access(cmd->heredoc, R_OK)
			inf = here_doc(cmd, redir->next->content);
			// inf = cmd->heredoc;
		if (redir->token == REDIR_OUT || redir->token == DREDIR_OUT)
			outf = redir_out(cmd, redir);
		redir = redir->next->next;
	}
	return (set_redir(cmd, inf, outf));
}
