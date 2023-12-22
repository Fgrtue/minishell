/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/20 15:15:43 by jiajchen      #+#    #+#                 */
/*   Updated: 2023/12/22 14:18:39 by jiajchen      ########   odam.nl         */
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

	hd = open("2", O_RDWR | O_CREAT | O_TRUNC, 0644);
	printf("Im %d from %s\n", hd, cmd->heredoc);
	if (hd == -1)
		perror("heredoc");
	line = readline("heredoc: ");
	while (ft_strncmp(line, inf, ft_strlen(inf)) != 0)
	{
		ft_putendl_fd(line, hd);
		free(line);
		line = readline("heredoc: ");
	}
	free(line);
	close(hd);
	return (cmd->heredoc);
}

// char*	redir_in(t_cmd*	cmd, t_lexer* redir)
// {
// 	if (redir->token == REDIR_IN)
// 	{
// 		cmd->hd_bool = 0;
// 		return(redir->next->content);
// 	}
// 	else if (redir->token == HERE_DOC)
// 	{
// 		cmd->hd_bool = here_doc(cmd, redir->next->content);
// 		return(cmd->heredoc);
// 	}
// 	else
// 		return (NULL);
// }

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

void set_redir(t_cmd *cmd, char *inf, char *outf)
{
	if (inf && (cmd->fd_io)[0] != 0)
		close((cmd->fd_io)[0]);
	if (outf && (cmd->fd_io)[1] != 1)
		close((cmd->fd_io)[1]);
	// printf("inf: %s\noutf: %s\n", inf, outf);
	if (outf && cmd->dr_bool == 1)
		(cmd->fd_io)[1] = open(outf, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (outf && cmd->dr_bool == 0)
		(cmd->fd_io)[1] = open(outf, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (inf)
		(cmd->fd_io)[0] = open(inf, O_RDONLY);
	if (access(cmd->heredoc, F_OK) == 0)
		unlink(cmd->heredoc);
	// printf("Redirections are %d %d\n", (cmd->fd_io)[0], (cmd->fd_io)[1]);
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
	static int	hd;

	inf = NULL;
	outf = NULL;
	redir = cmd->redir;
	cmd->heredoc = ft_itoa(++hd);
	while (redir)
	{
		if (redir->token == REDIR_IN)
			inf = redir->next->content;
		if (redir->token == HERE_DOC)
			inf = here_doc(cmd, redir->next->content);
		if (redir->token == REDIR_OUT || redir->token == DREDIR_OUT)
			outf = redir_out(cmd, redir);
		redir = redir->next->next;
	}
	set_redir(cmd, inf, outf);
}
