/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/07 10:10:35 by jiajchen      #+#    #+#                 */
/*   Updated: 2023/12/13 10:40:08 by jiajchen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


/* standard headers */
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
# include "../libft/libft.h"


t_lexer	*ft_lexnew(char *content, int token);
void	ft_lexaddfront(t_lexer** lexer, t_lexer* new);
void	ft_lexaddback(t_lexer **lexer, t_lexer *new);
t_lexer	*ft_lexlast(t_lexer* lexer);
void	ft_lexdel(t_lexer* node);
void	ft_lexclean(t_lexer** lexer);
void	ft_lexinsert(t_lexer **lst, t_lexer* prev, t_lexer* next, t_lexer* node);
t_lexer	*ft_lexretract(t_lexer **lst, t_lexer *node);

#endif