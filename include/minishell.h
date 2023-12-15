/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/07 10:10:35 by jiajchen      #+#    #+#                 */
/*   Updated: 2023/12/15 15:44:52 by jiajchen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* standard headers */
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>	// getcwd chdir / isatty ttyname ttyslot 
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>	// strerror
# include <errno.h>
# include <signal.h>	// signal kill sigaction sigemptyset sigaddset 
# include <sys/stat.h>	// stat lstat fstat
# include <dirent.h>	// opendir readdir closedir
# include <termio.h>	// tcsetattr tcgetattr
# include <readline/readline.h>
# include <readline/history.h>
# include "struct.h"
# include "lexer.h"
# include "../libft/libft.h"

void	expand_env(t_lexer **lst, char **env, int exit_c);
void	join_quotes(t_lexer **lst);
t_cmd	*get_cmds(t_lexer **lst, t_lexer *lexer);

t_cmd*	ft_cmdnew(void);
void	ft_cmdaddfront(t_cmd** cmd, t_cmd* new);
void	ft_cmdaddback(t_cmd** cmd, t_cmd* new);
t_cmd*	ft_cmdlast(t_cmd* cmd);
void	ft_cmddel(t_cmd* node);
void    ft_cmdclean(t_cmd** cmd);

void print_lex(t_lexer* lexer);
void print_cmd(t_cmd* cmd);

#endif